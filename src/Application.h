#ifndef ELEVEN_APPLICATION_H
#define ELEVEN_APPLICATION_H

#include "Eleven.h"
#include "Core/Core.h"
#include "Backend/OpenGL/OpenGLRenderer.h"
#include "Backend/DirectX12/DirectXRenderer.h"
#include "Backend/Vulkan/VulkanRenderer.h"
#include "Backend/Abstractions/IRendererAPI.h"

namespace el
{
    class Application
    {
    public:
        Application(u32 width, u32 height, EBackend backend);
        virtual ~Application();
        virtual void Run();

    private:
        virtual void CreateBackend();

    private:
        u32 _width;
        u32 _height;
        EBackend _backend;
        Unique<IRendererAPI> _renderer = nullptr;
    };
}

#endif //ELEVEN_APPLICATION_H
