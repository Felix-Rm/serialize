# serialize

[![build & test](https://github.com/Felix-Rm/serialize/actions/workflows/cmake.yml/badge.svg)](https://github.com/Felix-Rm/serialize/actions/workflows/cmake.yml)


## About

A simple c++ serialization / deserialization library.

## Usage

```cpp 
#include <serialize/core.hpp>
#include <serialize/io_providers/file_io.hpp>
#include <serialize/serializers/vector.hpp>
#include <serialize/serializers/integral.hpp>

// Serialize v1 and v2 into a file
void do_serialize(const char* filename, const std::vector<int>& v1, const std::vector<long>& v2){
    serialize::file_writer writer{filename};

    serialize::serialize(writer, v1);
    serialize::serialize(writer, v2);
}

// Deserialize v1 and v2 from a file
void do_deserialize(const char* filename, std::vector<int>& v1, std::vector<long>& v2){
    serialize::file_reader reader{filename};

    serialize::deserialize(reader, v1);
    serialize::deserialize(reader, v2);
}
```

(You can install the library header files with `make install` or just copy them into the project.)

### Serializers 

Serializers describe how to serialize an object. Serializers for common data types and containers are already predefined in 'src/serializers/'.

You can add serializers for your custom data types by specializing `serialize::serializer`.

```cpp
struct pod_type {
    int a;
    double b;
};

struct complex_type {
    std::vector<int> v;
};

namespace serialize {
    // Use this macro to create serializers for pod types
    SERIALIZE_GENERATE_MEMORY_SERIALIZER_FOR_TYPE(pod_type);

    // For more complex types you have to write explicit specializations
    template <>
    struct serializer<complex_type> {
        template <typename IoProvider>
        static void serialize(IoProvider& io_provider, const complex_type& data) {
            serializer<decltype(data.v)>::serialize(io_provider, data.v);
        }

        template <typename IoProvider>
        static void deserialize(IoProvider& io_provider, complex_type& data) {
            serializer<decltype(data.v)>::deserialize(io_provider, data.v);
        }
    };
}
```

### Io-Providers

Io-Providers describe the actual endpoints the data is written to. They are objects implementing a read and / or write method with the following signatures:

```cpp 
struct dummy_io_provider{
    void read(void* buffer, std::size_t len) {
        // Code for actually reading into the buffer from somewhere
    }

    void write(const void* buffer, std::size_t len) {
        // Code for actually writing the buffer somewhere
    }
}
```

An Io-Provider for reading and writing to / from files is provided in 'src/io_providers'.

