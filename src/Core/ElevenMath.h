#ifndef ELEVEN_ELEVENMATH_H
#define ELEVEN_ELEVENMATH_H
#include "../eleven.h"

namespace Eleven
{
    struct vec2
    {
        float x;
        float y;
        vec2() = default;
        vec2(const vec2&) = default;
        vec2& operator=(const vec2&) = default;
        vec2(vec2&&) = default;
        vec2& operator=(vec2&&) = default;
        constexpr vec2(float _x, float _y) : x(_x), y(_y) {}
        explicit vec2(_In_reads_(2) const float *pArray) : x(pArray[0]), y(pArray[1]) {}
    };

    struct vec3
    {
        float x;
        float y;
        float z;
        vec3() = default;
        vec3(const vec3&) = default;
        vec3& operator=(const vec3&) = default;
        vec3(vec3&&) = default;
        vec3& operator=(vec3&&) = default;
        constexpr vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
        explicit vec3(_In_reads_(3) const float *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}
    };

    const struct Vertex
    {
        vec2 pos;
        vec3 colour;

        Vertex() {}
        Vertex(float x, float y, float r, float g, float b)
            : pos( x, y ), colour( r, g, b ) {}
    };
}

#endif //ELEVEN_ELEVENMATH_H
