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