#include "lib.h"

void TokenPC::produce(const std::string& token) {
    tokens_.push(token);
}

std::string TokenPC::consume() {
    auto token = tokens_.front();
    tokens_.pop();

    if (transform_.has_value()) {
        return (*transform_)(token);
    }

    return token;
}

void TokenPC::set_transform(std::function<std::string(std::string)> transform) {
    transform_ = transform;
}

size_t TokenPC::size() const {
    return tokens_.size();
}

std::vector<int> heap_sort(const std::vector<int>& vec, Heap& heap) {
    for (int x : vec) {
        heap.insert(x);
    }

    std::vector<int> result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result.push_back(heap.get_max());
    }
    return result;
}