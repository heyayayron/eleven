#ifndef ELEVEN_ELEVENMATH_H
#define ELEVEN_ELEVENMATH_H

namespace el
{
    struct v2
    {
        float x;
        float y;
        v2() = default;
        v2(const v2&) = default;
        v2& operator=(const v2&) = default;
        v2(v2&&) = default;
        v2& operator=(v2&&) = default;
        constexpr v2(float _x, float _y) : x(_x), y(_y) {}
        explicit v2(_In_reads_(2) const float *pArray) : x(pArray[0]), y(pArray[1]) {}
    };

    struct v3
    {
        float x;
        float y;
        float z;
        v3() = default;
        v3(const v3&) = default;
        v3& operator=(const v3&) = default;
        v3(v3&&) = default;
        v3& operator=(v3&&) = default;
        constexpr v3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
        explicit v3(_In_reads_(3) const float *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}
    };

    const struct Vertex
    {
        v3 pos;
        v3 colour;

        Vertex() {}
        Vertex(float x, float y, float z, float r, float g, float b)
            : pos( x, y, z ), colour( r, g, b ) {}
    };
}

#endif //ELEVEN_ELEVENMATH_H
