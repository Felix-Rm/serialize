#pragma once

#include <string>

#include "../core.hpp"

namespace serialize {

template <>
struct serializer<std::string> {
    template <typename IoProvider>
    static void serialize(IoProvider& io_provider, const std::string& data) {
        std::size_t size = data.size();
        io_provider.write(&size, sizeof(size));
        io_provider.write(data.data(), size);
    }

    template <typename IoProvider>
    static void deserialize(IoProvider& io_provider, std::string& data) {
        std::size_t size;
        io_provider.read(&size, sizeof(size));
        data.resize(size);

        io_provider.read(&data[0], size);
    }
};

}  // namespace serialize