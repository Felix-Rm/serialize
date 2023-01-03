#pragma once

#include <vector>

#include "../core.hpp"

namespace serialize {

template <typename T>
struct serializer<std::vector<T>> {
    template <typename IoProvider>
    static void serialize(IoProvider& io_provider, const std::vector<T>& data) {
        std::size_t size = data.size();
        io_provider.write(&size, sizeof(size));

        for (const auto& element : data)
            serializer<T>::serialize(io_provider, element);
    }

    template <typename IoProvider>
    static void deserialize(IoProvider& io_provider, std::vector<T>& data) {
        std::size_t size;
        io_provider.read(&size, sizeof(size));
        data.reserve(size);

        T element;
        for (std::size_t i = 0; i < size; ++i) {
            serializer<T>::deserialize(io_provider, element);
            data.emplace_back(std::move(element));
        }
    }
};

}  // namespace serialize