#include <queue>
#include <string>
#include <optional>

class TokenPC {
public:
    void produce(const std::string& token);
    std::string consume();

    void set_transform(std::function<std::string(std::string)> transform);

    size_t size() const;

private:
    std::optional<std::function<std::string(std::string)>> transform_;
    std::queue<std::string> tokens_;
};


class Heap {
public:
    virtual void insert(int x) = 0;
    virtual int get_max() = 0;
};

std::vector<int> heap_sort(const std::vector<int>& vec, Heap& heap);