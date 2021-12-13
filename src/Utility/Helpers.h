#ifndef ELEVEN_HELPERS_H
#define ELEVEN_HELPERS_H

namespace el
{
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            // Set a breakpoint on this line to catch DirectX API errors
            throw std::exception();
        }
    }
}
#endif //ELEVEN_HELPERS_H
