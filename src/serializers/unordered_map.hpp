#pragma once

#include <unordered_map>

#include "../core.hpp"

namespace serialize {

template <typename T, typename U>
struct serializer<std::unordered_map<T, U>> {
    template <typename IoProvider>
    static void serialize(IoProvider& io_provider, const std::unordered_map<T, U>& data) {
        std::size_t size = data.size();
        io_provider.write(&size, sizeof(size));

        for (const auto& element : data) {
            serializer<T>::serialize(io_provider, element.first);
            serializer<U>::serialize(io_provider, element.second);
        }
    }

    template <typename IoProvider>
    static void deserialize(IoProvider& io_provider, std::unordered_map<T, U>& data) {
        std::size_t size;
        io_provider.read(&size, sizeof(size));
        data.reserve(size);

        T key;
        U value;
        for (std::size_t i = 0; i < size; ++i) {
            serializer<T>::deserialize(io_provider, key);
            serializer<U>::deserialize(io_provider, value);
            data.emplace(std::move(key), std::move(value));
        }
    }
};

}  // namespace serialize