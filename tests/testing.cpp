#include <ftest/test_logging.hpp>
#include <queue>

#include "core.hpp"
#include "serializers/integral.hpp"
#include "serializers/string.hpp"
#include "serializers/unordered_map.hpp"
#include "serializers/unordered_set.hpp"
#include "serializers/vector.hpp"

struct queue_io {
    std::queue<uint8_t> data{};

    void write(const void* buffer, std::size_t len) {
        const uint8_t* buf = static_cast<const uint8_t*>(buffer);
        for (size_t i = 0; i < len; ++i)
            data.push(buf[i]);
    }

    void read(void* buffer, std::size_t len) {
        uint8_t* buf = static_cast<uint8_t*>(buffer);
        for (size_t i = 0; i < len; ++i) {
            buf[i] = data.front();
            data.pop();
        }
    }
};

template <typename T>
TestLogging::test_result test_integral() {
    queue_io io{};

    T data = static_cast<T>(rand());
    T reconstructed_data;

    serialize::serialize(io, data);
    serialize::deserialize(io, reconstructed_data);

    if (data != reconstructed_data) {
        return {"Reconstructed data is not equal to original"};
    }

    return {};
}

TestLogging::test_result test_string() {
    queue_io io{};

    size_t size = static_cast<size_t>(rand()) % 100;
    std::string data{};

    for (size_t i = 0; i < size; i++)
        data += '0' + rand() % 10;

    std::string reconstructed_data;

    serialize::serialize(io, data);
    serialize::deserialize(io, reconstructed_data);

    if (data != reconstructed_data) {
        return {"Reconstructed data is not equal to original"};
    }

    return {};
}

template <typename T>
TestLogging::test_result test_vector() {
    queue_io io{};

    size_t size = static_cast<size_t>(rand()) % 1000;

    std::vector<T> data{};

    for (size_t i = 0; i < size; ++i)
        data.push_back(static_cast<T>(rand()));

    std::vector<T> reconstructed_data;

    serialize::serialize(io, data);
    serialize::deserialize(io, reconstructed_data);

    if (data != reconstructed_data) {
        return {"Reconstructed data is not equal to original"};
    }

    return {};
}

template <typename T, typename U>
TestLogging::test_result test_map() {
    queue_io io{};

    size_t size = static_cast<size_t>(rand()) % 1000;

    std::unordered_map<T, U> data{};

    for (size_t i = 0; i < size; ++i)
        data.emplace(static_cast<T>(rand()), static_cast<U>(rand()));

    std::unordered_map<T, U> reconstructed_data;

    serialize::serialize(io, data);
    serialize::deserialize(io, reconstructed_data);

    if (data != reconstructed_data) {
        return {"Reconstructed data is not equal to original"};
    }

    return {};
}

template <typename T>
TestLogging::test_result test_set() {
    queue_io io{};

    size_t size = static_cast<size_t>(rand()) % 1000;

    std::unordered_set<T> data{};

    for (size_t i = 0; i < size; ++i)
        data.emplace(static_cast<T>(rand()));

    std::unordered_set<T> reconstructed_data;

    serialize::serialize(io, data);
    serialize::deserialize(io, reconstructed_data);

    if (data != reconstructed_data) {
        return {"Reconstructed data is not equal to original"};
    }

    return {};
}

int main() {
    TestLogging::start_suite("serialize");

    TestLogging::run("test_integral(char)", test_integral<char>);
    TestLogging::run("test_integral(int)", test_integral<int>);
    TestLogging::run("test_integral(long)", test_integral<long>);

    TestLogging::run("test_string", test_string);

    TestLogging::run("test_vector(long)", test_vector<long>);

    TestLogging::run("test_map(long,long)", test_map<long, long>);

    TestLogging::run("test_set(long)", test_set<long>);

    return TestLogging::results();
}