#include "elpch.h"
#include "Application.h"

namespace el
{
    Application::Application(u32 width, u32 height, EBackend backend)
    {
        if (width == NULL) throw std::exception("width is null");
        if (height == NULL) throw std::exception("height is null");
        if (backend == NULL) throw std::exception("backend is null");

        _width = width;
        _height = height;
        _backend = backend;

        CreateBackend();
    }

    Application::~Application()
    {
        _renderer.release();
        std::cout << "Application Closed\n";
    }

    void Application::CreateBackend()
    {
        switch (_backend) {
            case EBackend::NONE:
                std::cout << "Backend NONE(" << _backend << ") selected\n";
                _renderer = nullptr;
                break;
            case EBackend::OPENGL:
                std::cout << "Backend OPENGL(" << _backend << ") selected\n";
                _renderer = std::make_unique<OpenGLRenderer>(_width, _height);
                break;
            case EBackend::DIRECTX:
                std::cout << "Backend DIRECTX(" << _backend << ") selected\n";
                _renderer = std::make_unique<DirectXRenderer>(_width, _height);
                break;
            case EBackend::VULKAN:
                std::cout << "Backend VULKAN(" << _backend << ") selected\n";
                _renderer = std::make_unique<VulkanRenderer>(_width, _height);
                break;
        }
    }

    void Application::Run()
    {
        // Theoretically, we should be able to define a poly here and
        // the selected backend should be able to use it.

        /*
        Vertex vertices[3] =
        {
            Vertex(-0.6f, -0.4f, 1.f, 0.f, 0.f),
            Vertex(0.6f, -0.4f, 0.f, 1.f, 0.f),
            Vertex(0.f, 0.6f, 0.f, 0.f, 1.f)
        };
        */

        float x = -0.5;
        float y = -0.5;
        float width = 1, height = 1;
        Vertex vertices[4] =
        {
            Vertex(x, y, 0.f, 1.f, 0.f, 0.f),
            Vertex(x + width, y, 0.f, 0.f, 1.f, 0.f),
            Vertex(x + width, y + height, 0.f, 0.f, 1.f, 0.f),
            Vertex(x, y + height, 0.f, 0.f, 0.f, 1.f),
        };

        _renderer->Setup(vertices);
        _renderer->Render();
    }
}
