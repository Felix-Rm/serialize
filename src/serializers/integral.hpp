#pragma once

#include "../core.hpp"

namespace serialize {

#define SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(type)                \
    template <>                                                            \
    struct serializer<type> {                                              \
        template <typename IoProvider>                                     \
        static void serialize(IoProvider& io_provider, const type& data) { \
            io_provider.write(&data, sizeof(type));                        \
        }                                                                  \
                                                                           \
        template <typename IoProvider>                                     \
        static void deserialize(IoProvider& io_provider, type& data) {     \
            io_provider.read(&data, sizeof(type));                         \
        }                                                                  \
    };

SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(char)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(unsigned char)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(short)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(unsigned short)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(int)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(unsigned int)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(long)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(unsigned long)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(long long)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(unsigned long long)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(float)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(double)
SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(long double)

}  // namespace serialize