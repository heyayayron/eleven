#ifndef ELEVEN_IRENDERERAPI_H
#define ELEVEN_IRENDERERAPI_H

#include "../../elpch.h"
#include "../../Core/Core.h"
#include "../../Core/ElevenMath.h"

namespace el
{
    enum EBackend
    {
        OPENGL = 1,
        DIRECTX = 2,
        VULKAN = 3,
        NONE = 4
    };

    class IRendererAPI
    {
    public:
        virtual void Setup(Vertex *vertices) = 0;
        virtual void Render() = 0;

    protected:
        i32 _width;
        i32 _height;

        Vertex* _vertices;
        GLFWwindow* _gfxContext;
    };
}

#endif //ELEVEN_IRENDERERAPI_H
