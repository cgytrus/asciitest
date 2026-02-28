#pragma once

#include <string>
#include <array>
#include <glad/gl.h>

class Shader {
public:
    GLuint program() { return m_program; }

    template<size_t VertexSize, size_t FragmentSize>
    bool compile(
        const unsigned char (&vertexSource)[VertexSize],
        const unsigned char (&fragmentSource)[FragmentSize]
    ) {
        return this->compile(
            std::string{reinterpret_cast<char const* const>(vertexSource), VertexSize},
            std::string{reinterpret_cast<char const* const>(fragmentSource), FragmentSize}
        );
    }

    bool compile(std::string vertexSource, std::string fragmentSource);
    bool link();
    void cleanup();

private:
    GLuint m_vertex = 0;
    GLuint m_fragment = 0;
    GLuint m_program = 0;
};
