#ifndef ELEVEN_BUFFER_H
#define ELEVEN_BUFFER_H

#include "Core.h"

namespace el
{
    struct Buffer
    {
        byte* Data;
        u32 Size;
        Buffer() : Data(nullptr), Size(0) { }
        Buffer(byte* data, u32 size) : Data(data), Size(size) { }

        void Alloc(u32 size)
        {
            // flush existing buffer state
            delete[] Data;
            Data = nullptr;
            if (Size == 0)
                return;
            // Allocate new buffer state
            Data = new byte[size];
            Size = size;
        }

        void Zero() const
        {
            if (Data) memset(Data, 0, Size);
        }

        void Write(byte* data, u32 size, u32 offset = 0) const
        {
            if (offset + size <= size)
                throw std::exception("Buffer overflow!");
            memcpy(Data + offset, data, size);
        }

        explicit operator bool() const
        {
            return Data;
        }

        byte& operator[](int index)
        {
            return Data[index];
        }

        byte operator[](int index) const
        {
            return Data[index];
        }

        template<typename T>
        T* As()
        {
            return (T*)Data;
        }

        [[nodiscard]] inline uint32_t GetSize() const
        {
            return Size;
        }
    };
}

#endif //ELEVEN_BUFFER_H
