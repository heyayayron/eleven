#include "OpenGLShader.h"

namespace el
{
    OpenGLShader::OpenGLShader(const std::string &shaderPath)
        : IShader(shaderPath)
    {
        ReloadShader();
    }

    void OpenGLShader::ReloadShader()
    {
        size_t found = _path.find_last_of("/\\");
        _name = found != std::string::npos ? _path.substr(found + 1) : _path;

        std::string shaderSource = LoadShaderFile();
        _shaderSources = PreprocessShaders(shaderSource);
        CompileAndSubmitToDevice();
    }

    u32 OpenGLShader::Use()
    {
        glUseProgram(_shaderId);
        return _shaderId;
    }

    u32 OpenGLShader::GetId()
    {
        return _shaderId;
    }

    u32 OpenGLShader::GetVertexVar(const std::string &name)
    {
        u32 result = glGetUniformLocation(_shaderId, name.c_str());
        if (result == -1)
            std::cout << "Couldn't find [uniform] vertex_var " << name << " in shader " << _name << "\n"; // note: might not compile in gcc
        return result;
    }

    u32 OpenGLShader::GetVertexInvariant(const std::string &name)
    {
        u32 result = glGetAttribLocation(_shaderId, name.c_str());
        if (result == -1)
            std::cout << "Couldn't find [attribute] vertex_invariant " << name << " in shader " << _name << "\n";
        return result;
    }

    u32 OpenGLShader::GetFragmentVar(const std::string &name)
    {
        throw std::exception("GetFragmentVar not implemented for OpenGLShader");
    }

    u32 OpenGLShader::GetFragmentInvariant(const std::string &name)
    {
        throw std::exception("GetFragmentInvariant not implemented for OpenGLShader");
    }

    void OpenGLShader::SetFragmentVar1f(const std::string &name, float& input)
    {
        u32 location = GetVertexVar(name);
        glUniform1f(location, input);
    }

    void OpenGLShader::SetFragmentVar2f(const std::string &name, float& x, float& y)
    {
        u32 location = GetVertexVar(name);
        glUniform2f(location, x, y);
    }

    void OpenGLShader::SetFragmentVar3f(const std::string &name, float& x, float& y, float& z)
    {
        u32 location = GetVertexVar(name);
        glUniform3f(location, x, y, z);
    }

    void OpenGLShader::SetFragmentMat4fv(const std::string &name, mat4x4& mat)
    {
        u32 location = GetVertexVar(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat *) mat);
    }

    template<class T>
    T ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return (T)GL_VERTEX_SHADER;
        else if (type == "fragment" || type == "pixel")
            return (T)GL_FRAGMENT_SHADER;
        else throw std::exception("Invalid Shader Type");
    }

    std::string OpenGLShader::LoadShaderFile()
    {
        std::string result;
        std::ifstream in(_path, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            std::cout << "Could not read shader file " << _path << "\n";
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreprocessShaders(const std::string &source)
    {
        std::unordered_map<GLenum, std::string> shaderSources;
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while(pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            if (type != "vertex" && type != "fragment" && type != "pixel")
                std::cout << "shader type <" << type << "> not valid\n";
            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString<GLenum>(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }
        return shaderSources;
    }

    void OpenGLShader::CompileAndSubmitToDevice()
    {
        std::vector<GLuint> _shaderRenderIds;
        GLuint program = glCreateProgram();
        for(auto& kv : _shaderSources)
        {
            GLenum type = kv.first;
            std::string& source = kv.second;
            GLuint shaderRendererId = glCreateShader(type);
            const GLchar* sourceCstring = (const GLchar*)source.c_str();

            glShaderSource(shaderRendererId, 1, &sourceCstring, 0);
            glCompileShader(shaderRendererId);

            GLint isCompiled = 0;
            glGetShaderiv(shaderRendererId, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shaderRendererId, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shaderRendererId, maxLength, &maxLength, &infoLog[0]);

                std::cout << "Shader compilation failed: \n\t" << &infoLog[0] << "\n";

                // We don't need the shader anymore.
                glDeleteShader(shaderRendererId);
            }

            _shaderRenderIds.push_back(shaderRendererId);
            glAttachShader(program, shaderRendererId);
        }

        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            throw std::exception("Shader compilation failed:\n" + infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);

            // Don't leak shaders either.
            for (auto id : _shaderRenderIds)
                glDeleteShader(id);
        }

        // Always detach shaders after a successful link.
        for (auto id : _shaderRenderIds)
            glDetachShader(program, id);

        _shaderId = program;
    }
}