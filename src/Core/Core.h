#ifndef ELEVEN_CORE_H
#define ELEVEN_CORE_H

#include "../elpch.h"

namespace el
{
    // Type aliasing
    // Why? because it's easier for me to read.

    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;
    using byte = unsigned char;

    template<typename T>
    using Unique = std::unique_ptr<T>;

    template<typename T>
    using Shared = std::shared_ptr<T>;

    template<typename T>
    using Weak = std::weak_ptr<T>;
}
#endif //ELEVEN_CORE_H
