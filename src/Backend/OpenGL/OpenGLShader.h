#ifndef ELEVEN_OPENGLSHADER_H
#define ELEVEN_OPENGLSHADER_H

#include "../../Core/Core.h"

#include "../../Core/linmath.h"
#include "../Abstractions/IRendererAPI.h"
#include "../Abstractions/IShader.h"

namespace el
{
    class OpenGLShader : public IShader<GLenum>
    {
    public:
        explicit OpenGLShader(const std::string &shaderPath);
        ~OpenGLShader() = default;
        void ReloadShader() override;
        std::string LoadShaderFile() override;
        void CompileAndSubmitToDevice() override;

        u32 Use() override;
        u32 GetId() override;
        u32 GetVertexVar(const std::string& name) override;
        u32 GetVertexInvariant(const std::string& name) override;
        u32 GetFragmentVar(const std::string& name) override;
        u32 GetFragmentInvariant(const std::string& name) override;
        void SetFragmentVar1f(const std::string &name, float& input) override;
        void SetFragmentVar2f(const std::string &name, float& x, float& y) override;
        void SetFragmentVar3f(const std::string &name, float& x, float& y, float& z) override;
        void SetFragmentMat4fv(const std::string &name, mat4x4& mat) override;

    private:
        std::unordered_map<GLenum, std::string> PreprocessShaders(const std::string &source);
    };
}

#endif //ELEVEN_OPENGLSHADER_H
