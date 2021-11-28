#pragma once

#include "mipt/journal/journal.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <optional>

namespace mipt {

enum LogEvent {
    INSERT_KEY = 0x00,
    ERASE_KEY = 0x01,
};

std::string to_string(LogEvent event) {
    switch (event) {
    case INSERT_KEY:
        return "INSERT";
    case ERASE_KEY:
        return "ERASE";
    default:
        assert(0);
    }
}

template<class T>
struct LogEntry {
    LogEvent event;
    T key;
    bool applied = false;
} __attribute__((packed));

template<class T>
class FlatSet {
public:
    using JournalType = Journal<FlatSet<T>, LogEntry<T>>;

public:
    FlatSet(std::optional<std::string_view> path = std::nullopt, OptimizeLevel optlevel = OptimizeLevel::NONE) 
    {
        if (path.has_value()) {
            journal_ = new JournalType(*path, this, optlevel);
            journal_->LoadState();
        }

        keys_.reserve(kInitialSize);
    }

    ~FlatSet()
    {
        if (journal_ != nullptr) {
            delete journal_;
        }
    }

    bool insert(const T& value) {
        if (exists(value)) {
            return false;
        }

        if (journal_) {
            journal_->Write(LogEntry<T>{LogEvent::INSERT_KEY, value});
        }
        keys_.push_back(value);

        std::sort(keys_.begin(), keys_.end());
        return true;
    }

    bool exists(const T& value) const {
        auto found = std::lower_bound(keys_.begin(), keys_.end(), value);
        if (found == keys_.end()) {
            return false;
        }

        return *found == value;
    }

    bool erase(const T& value) {
        auto found = std::lower_bound(keys_.begin(), keys_.end(), value);
        if (found == keys_.end()) {
            return false;
        }

        if (journal_) {
            journal_->Write(LogEntry<T>{LogEvent::ERASE_KEY, value});
        }
        keys_.erase(found);
        return true;
    }
    
    size_t size() const {
        return keys_.size();
    }

    bool is_empty() const {
        return size() == 0;
    }

private:
    void Write(std::ostream& out) const {
        size_t size = keys_.size();
        out.write((char*)&size, sizeof(size));
        out.write((char*)keys_.data(), size * sizeof(T));
    }

    void Read(std::istream& in) {
        size_t size;
        in.read((char*)&size, sizeof(size));
        keys_.resize(size);
        in.read((char*)keys_.data(), size * sizeof(T));
    }

    bool Apply(LogEntry<T>* entry) {
        INFOV() << "Read entry: action(" << to_string(entry->event) << ") value(" << entry->key << ")" << std::endl;

        bool status;
        switch (entry->event) {
        case LogEvent::INSERT_KEY:
            status = insert(entry->key);
            break;
        case LogEvent::ERASE_KEY:
            status = erase(entry->key);
            break;
        }

        entry->applied = true;
        return status;
    }

    void ApplyBatch(std::vector<LogEntry<T>*>& entries) {
        auto buffer_set = FlatSet<T>();

        for (auto* entry : entries) {
            if (!Apply(entry)) {
                entry->applied = false;
            }
        }

        for (const auto& key : buffer_set.keys_) {
            insert(key);
        }
    }


private:
    friend class Journal<FlatSet<T>, LogEntry<T>>;
    static const size_t kInitialSize = 1024;

private:
    JournalType* journal_ = nullptr;   
    std::vector<T> keys_;
};

}