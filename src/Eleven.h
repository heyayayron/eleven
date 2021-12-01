#ifndef ELEVEN_ELEVEN_H
#define ELEVEN_ELEVEN_H

#include <intsafe.h>
#include <exception>
#include <cstdint>

typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

enum EBackend
{
    OPENGL = 1,
    DIRECTX = 2,
    NONE = 3
};

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        // Set a breakpoint on this line to catch DirectX API errors
        throw std::exception();
    }
}

#endif //ELEVEN_ELEVEN_H
