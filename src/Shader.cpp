#include "Shader.hpp"
#include <fmt/base.h>

bool Shader::compile(std::string vertexSource, std::string fragmentSource) {
    auto getShaderLog = [](GLuint id) -> std::string {
        GLint length, written;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        if (length <= 0)
            return "";
        auto stuff = new char[length + 1];
        glGetShaderInfoLog(id, length, &written, stuff);
        std::string result(stuff);
        delete[] stuff;
        return result;
    };
    GLint res;

    m_vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSources[] = {
        vertexSource.c_str()
    };
    glShaderSource(m_vertex, sizeof(vertexSources) / sizeof(char*), vertexSources, nullptr);
    glCompileShader(m_vertex);
    auto vertexLog = getShaderLog(m_vertex);

    glGetShaderiv(m_vertex, GL_COMPILE_STATUS, &res);
    if(!res) {
        glDeleteShader(m_vertex);
        m_vertex = 0;
        fmt::println("vertex shader compilation failed:\n{}", vertexLog);
        return false;
    }

    if (vertexLog.empty()) {
        fmt::println("vertex shader compilation successful");
    }
    else {
        fmt::println("vertex shader compilation successful:\n{}", vertexLog);
    }

    m_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSources[] = {
        fragmentSource.c_str()
    };
    glShaderSource(m_fragment, sizeof(vertexSources) / sizeof(char*), fragmentSources, nullptr);
    glCompileShader(m_fragment);
    auto fragmentLog = getShaderLog(m_fragment);

    glGetShaderiv(m_fragment, GL_COMPILE_STATUS, &res);
    if(!res) {
        glDeleteShader(m_vertex);
        glDeleteShader(m_fragment);
        m_vertex = 0;
        m_fragment = 0;
        fmt::println("fragment shader compilation failed:\n{}", fragmentLog);
        return false;
    }

    if (fragmentLog.empty()) {
        fmt::println("fragment shader compilation successful");
    }
    else {
        fmt::println("fragment shader compilation successful:\n{}", fragmentLog);
    }

    m_program = glCreateProgram();
    glAttachShader(m_program, m_vertex);
    glAttachShader(m_program, m_fragment);

    return true;
}

bool Shader::link() {
    if (!m_vertex) {
        fmt::println("vertex shader not compiled");
        return false;
    }
    if (!m_fragment) {
        fmt::println("fragment shader not compiled");
        return false;
    }

    auto getProgramLog = [](GLuint id) -> std::string {
        GLint length, written;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        if (length <= 0)
            return "";
        auto stuff = new char[length + 1];
        glGetProgramInfoLog(id, length, &written, stuff);
        std::string result(stuff);
        delete[] stuff;
        return result;
    };
    GLint res;

    glLinkProgram(m_program);
    auto programLog = getProgramLog(m_program);

    glDeleteShader(m_vertex);
    glDeleteShader(m_fragment);
    m_vertex = 0;
    m_fragment = 0;

    glGetProgramiv(m_program, GL_LINK_STATUS, &res);
    if(!res) {
        glDeleteProgram(m_program);
        m_program = 0;
        fmt::println("shader link failed:\n{}", programLog);
        return false;
    }

    if (programLog.empty()) {
        fmt::println("shader link successful");
    }
    else {
        fmt::println("shader link successful:\n{}", programLog);
    }

    return true;
}

void Shader::cleanup() {
    if (m_program)
        glDeleteProgram(m_program);
    m_program = 0;
}
