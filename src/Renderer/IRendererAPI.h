#ifndef ELEVEN_IRENDERERAPI_H
#define ELEVEN_IRENDERERAPI_H

#include <GLFW/glfw3.h>
#include "../Eleven.h"
#include "../Core/ElevenMath.h"

class IRendererAPI
{
public:
    virtual void Setup(Eleven::Vertex* vertices) = 0;
    virtual void Render() = 0;
protected:
    i32 _width;
    i32 _height;

    Eleven::Vertex* _vertices;
    GLFWwindow* _oglContext;
    GLFWwindow* _dxContext;
    GLFWwindow* _vkContext;
    GLFWwindow* _wglContext;
    GLFWwindow* _mtlContext;
};


#endif //ELEVEN_IRENDERERAPI_H
