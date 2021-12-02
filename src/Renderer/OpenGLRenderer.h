#ifndef ELEVEN_OPENGLRENDERER_H
#define ELEVEN_OPENGLRENDERER_H

#include <GLFW/glfw3.h>
#include "IRendererAPI.h"
#include "../Eleven.h"

class OpenGLRenderer : public IRendererAPI
{
public:
    OpenGLRenderer(const u32 width, const u32 height);
    ~OpenGLRenderer();
    void Render() override;
    void Setup(Eleven::Vertex* vertices) override;
};

#endif //ELEVEN_OPENGLRENDERER_H
