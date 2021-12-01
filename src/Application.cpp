#include <iostream>
#include <map>
#include "Application.h"

Application::Application(u32 width, u32 height, EBackend backend)
{
    if (width == NULL) throw "width is null";
    if (height == NULL) throw "height is null";
    if (backend == NULL) throw "backend is null";

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
    switch (_backend)
    {
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
    }
}

void Application::Run()
{
    Eleven::Vertex vertices[3] =
    {
            Eleven::Vertex(-0.6f, -0.4f, 1.f, 0.f, 0.f ),
            Eleven::Vertex(0.6f, -0.4f, 0.f, 1.f, 0.f ),
            Eleven::Vertex(0.f,  0.6f, 0.f, 0.f, 1.f )
    };

    _renderer->Setup(vertices);
    _renderer->Render();
}