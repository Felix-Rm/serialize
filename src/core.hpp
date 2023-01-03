#pragma once

namespace serialize {

template <typename T>
struct serializer {
    template <typename IoProvider>
    static void serialize(IoProvider& io_provider, const T& data) = delete;

    template <typename IoProvider>
    static void deserialize(IoProvider& io_provider, T& data) = delete;
};

template <typename Writer, typename T>
inline void serialize(Writer&& writer, const T& data) {
    serializer<T>::serialize(writer, data);
}

template <typename Reader, typename T>
inline void deserialize(Reader&& reader, T& data) {
    serializer<T>::deserialize(reader, data);
}

}  // namespace serialize