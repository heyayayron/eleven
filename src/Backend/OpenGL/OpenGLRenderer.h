#ifndef ELEVEN_OPENGLRENDERER_H
#define ELEVEN_OPENGLRENDERER_H

#include "../../Core/Core.h"

#include "../../Core/linmath.h"
#include "../Abstractions/IRendererAPI.h"
#include "../Abstractions/IShader.h"

namespace el
{
    class OpenGLRenderer : public IRendererAPI
    {
    private:
        Unique<IShader<GLenum>> _basicShader = nullptr;
    public:
        OpenGLRenderer(const u32 width, const u32 height);
        ~OpenGLRenderer();
        void Render() override;
        void Setup(Vertex *vertices) override;
    };
}

#endif //ELEVEN_OPENGLRENDERER_H
