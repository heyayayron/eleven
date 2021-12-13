#ifndef ELEVEN_ISHADER_H
#define ELEVEN_ISHADER_H

namespace el
{
    enum EShaderType
    {
        UNIFIED,
        VERTEX,
        FRAGMENT,
        PIXEL,
        COMPUTE,
        UNKNOWN
    };

    template<typename ShaderType>
    class IShader
    {
    public:
        IShader(const std::string& shaderPath) : _path(shaderPath) {}

        virtual void ReloadShader() = 0;
        virtual std::string LoadShaderFile() = 0;
        virtual void CompileAndSubmitToDevice() = 0;
        virtual u32 Use() = 0;
        virtual u32 GetId() = 0;

        // Uniform
        [[nodiscard]] virtual u32 GetVertexVar(const std::string& name) = 0;
        // Attribute
        [[nodiscard]] virtual u32 GetVertexInvariant(const std::string& name) = 0;
        [[nodiscard]] virtual u32 GetFragmentVar(const std::string& name) = 0;
        [[nodiscard]] virtual u32 GetFragmentInvariant(const std::string& name) = 0;

        virtual void SetFragmentVar1f(const std::string &name, float& input) = 0;
        virtual void SetFragmentVar2f(const std::string &name, float& x, float& y) = 0;
        virtual void SetFragmentVar3f(const std::string &name, float& x, float& y, float& z) = 0;
        virtual void SetFragmentMat4fv(const std::string &name, mat4x4& mat) = 0;

    protected:
        u32 _shaderId;
        std::string _name;
        std::string _path;
        std::unordered_map<ShaderType, std::string> _shaderSources;
    };
}

#endif //ELEVEN_ISHADER_H
