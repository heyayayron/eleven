#include "../../elpch.h"
#include "OpenGLRenderer.h"
#include "OpenGLShader.h"

namespace el
{
    void error_callback(int error, const char *description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    float frameCount = 0;
    GLuint vertex_buffer;
    GLint mvp_location, vpos_location, vcol_location, vtime_location;

    OpenGLRenderer::OpenGLRenderer(const u32 width, const u32 height) : IRendererAPI() {
        _width = width;
        _height = height;

        if (!glfwInit())
        {
            std::cout << "GLFW: failed to initialise.\n";
        }

        glfwSetErrorCallback(error_callback);

        _gfxContext = glfwCreateWindow(_width, _height, "Eleven (OpenGL 3.2)", NULL, NULL);
        if (!_gfxContext)
        {
            std::cout << "GLFW: failed to create window\n";
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        glfwSetKeyCallback(_gfxContext, key_callback);
        glfwMakeContextCurrent(_gfxContext);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            std::cout << "GLAD: Failed to initialize OpenGL context\n";
        }
        glfwShowWindow(_gfxContext);
    }

    OpenGLRenderer::~OpenGLRenderer()
    {
        glfwDestroyWindow(_gfxContext);
        delete _gfxContext;
    }

    void OpenGLRenderer::Setup(el::Vertex *vertices)
    {
        _basicShader = std::make_unique<OpenGLShader>("assets/shaders/basic.shader");

        _vertices = vertices;
        // u32 length = 3; // TODO: Determine size at runtime
        auto vertsize = sizeof(_vertices[0]);

        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertsize * sizeof(el::Vertex), _vertices, GL_STATIC_DRAW);

        mvp_location = _basicShader->GetVertexVar("MVP");
        vtime_location = _basicShader->GetVertexVar("vTime");
        vpos_location = _basicShader->GetVertexInvariant("vPos");
        vcol_location = _basicShader->GetVertexInvariant("vCol");

        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                              sizeof(_vertices[0]), (void *) 0);
        glEnableVertexAttribArray(vcol_location);
        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                              sizeof(_vertices[0]), (void *) (sizeof(float) * 2));
    }

    void OpenGLRenderer::Render()
    {
        glfwSwapInterval(1);

        while (!glfwWindowShouldClose(_gfxContext)) {
            float ratio;
            mat4x4 m, p, mvp;

            glfwGetFramebufferSize(_gfxContext, &_width, &_height);
            ratio = _width / (float) _height;

            glViewport(0, 0, _width, _height);
            glClearColor(1.0f, 0.2f, 0.4f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            mat4x4_identity(m);
            mat4x4_rotate_Z(m, m, (float) glfwGetTime());
            mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            mat4x4_mul(mvp, p, m);

            _basicShader.get()->Use();
            _basicShader.get()->SetFragmentMat4fv("MVP", mvp);
            _basicShader.get()->SetFragmentVar1f("vTime", frameCount); // currently vTime is just the frame number

            glDrawArrays(GL_QUADS, 0, 4);

            glfwSwapBuffers(_gfxContext);
            glfwPollEvents();
            frameCount++;
        }
    }
}