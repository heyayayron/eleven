#ifndef ELEVEN_APPLICATION_H
#define ELEVEN_APPLICATION_H

#include <GLFW/glfw3.h>
#include "Eleven.h"
#include "Renderer/OpenGLRenderer.h"
#include "Renderer/DirectXRenderer.h"
#include "Renderer/IRendererAPI.h"

class Application
{
public:
    Application(u32 width, u32 height, EBackend backend);
    virtual ~Application();
    void Run();

private:
    void CreateBackend();

private:
    u32 _width;
    u32 _height;
    EBackend _backend;
    std::unique_ptr<IRendererAPI> _renderer = nullptr;
};

#endif //ELEVEN_APPLICATION_H
