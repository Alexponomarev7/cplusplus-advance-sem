#pragma once

#include <memory>
#include <fstream>
#include <filesystem>

#include "mipt/log/log.h"

namespace mipt {

namespace fs = std::filesystem;

enum OptimizeLevel {
    NONE,
    STRONG
};

template<class T, class JournalEntry>
class Journal {
public:
    explicit Journal(std::filesystem::path path, T* structure, OptimizeLevel optlevel = OptimizeLevel::NONE
        , size_t snapshot_frequency = 128) 
        : structure_(structure)
        , path_(path)
        , snapshot_frequency_(snapshot_frequency)
        , optlevel_(optlevel)
    {
        if (optlevel == OptimizeLevel::STRONG) {
            INFO() << "Create journal in STRONG optimization mode!" << std::endl;
        }

        fs::create_directories(path);
        log_ = std::ofstream(path / "log", std::ios_base::app);
        UpdateEpoch();
    }

    void LoadState() {
        UpdateEpoch();
        size_t offset_actions = 0;
        if (epoch_ != 0) {
            INFO() << "Read snapshot version: " << last_snapshot_ - 1 << std::endl;

            std::ifstream snapshot_in(path_ / std::to_string(last_snapshot_ - 1));
            
            snapshot_in.read((char*)&offset_actions, sizeof(offset_actions));
            structure_->Read(snapshot_in);
        }
        std::ifstream log_in(path_ / "log");
        log_in.seekg(offset_actions);

        switch (optlevel_) {
        case OptimizeLevel::NONE: {
            JournalEntry entry;
            while (log_in.read((char*)&entry, sizeof(entry))) {
                structure_->Apply(&entry);
                assert(entry.applied);
            }
            break;
        }
        case OptimizeLevel::STRONG: {
            std::vector<JournalEntry> entries;
            std::vector<JournalEntry*> entries_ptr;
            entries.reserve(snapshot_frequency_);
            entries_ptr.reserve(snapshot_frequency_);

            JournalEntry entry;
            while (log_in.read((char*)&entry, sizeof(entry))) {
                entries.push_back(entry);
                entries_ptr.push_back(&entries.back());
            }

            structure_->ApplyBatch(entries_ptr);
            break;
        }
        default:
            assert(0);
        }
    }

    void Write(JournalEntry entry) {
        log_.write((char*)&entry, sizeof(entry));
        epoch_++;

        if (epoch_ % snapshot_frequency_ == 0) {
            std::ofstream out(path_ / std::to_string(last_snapshot_));
            last_snapshot_++;

            size_t offset_actions = log_.tellp();;
            out.write((char*)&offset_actions, sizeof(offset_actions));
            structure_->Write(out);
        }
    }

private:
    void UpdateEpoch() {
        while (fs::exists(path_ / std::to_string(last_snapshot_))) {
            last_snapshot_++;
        }
    }

    T* structure_;
    fs::path path_;
    std::ofstream log_;
    const int snapshot_frequency_;
    size_t epoch_ = 0;
    size_t last_snapshot_ = 0;
    OptimizeLevel optlevel_ = OptimizeLevel::NONE;
};

}