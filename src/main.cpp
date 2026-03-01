#include <fmt/base.h>
#include <asp/time.hpp>

#include <glad/gl.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define RGFW_OPENGL
#define RGFW_USE_XDL
#define RGFW_ALLOC_DROPFILES
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_DEBUG
#define GL_SILENCE_DEPRECATION
#include <RGFW.h>

#include "Shader.hpp"

#include <default.vert.h>
#include <default.frag.h>

#include <mat.vert.h>
#include <mat.frag.h>

struct {
    GLuint vao;
    GLuint vbo;

    void setup() {
        float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void draw() {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }
} s_cube;

struct {
    GLuint vao;
    GLuint vbo;

    void setup() {
        float vertices[] = {
            -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void draw() {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }
} s_quad;

int main() {
    RGFW_glHints* hints = RGFW_getGlobalHints_OpenGL();
    hints->major = 3;
    hints->minor = 3;
    hints->profile = RGFW_glCore;
    hints->debug = true;
    hints->noError = false;
    RGFW_setGlobalHints_OpenGL(hints);

    RGFW_window* window = RGFW_createWindow(
        "asciitest",
        0, 0,
        1280, 720,
        RGFW_windowAllowDND | RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowOpenGL
    );
    if (window == nullptr) {
        fmt::println("Failed to create RGFW window");
        return -1;
    }
    RGFW_window_setExitKey(window, RGFW_escape);
    RGFW_window_makeCurrentContext_OpenGL(window);

    int version = gladLoadGL(&RGFW_getProcAddress_OpenGL);
    if (version == 0) {
        fmt::println("Failed to initialize GLAD");
        return -1;
    }

    fmt::println("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        const char* sourceStr;
        const char* typeStr;
        const char* severityStr;

        switch (source) {
            case GL_DEBUG_SOURCE_API:
                sourceStr = "API";
                break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                sourceStr = "WINDOW SYSTEM";
                break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                sourceStr = "SHADER COMPILER";
                break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                sourceStr = "THIRD PARTY";
                break;
            case GL_DEBUG_SOURCE_APPLICATION:
                sourceStr = "APPLICATION";
                break;
            case GL_DEBUG_SOURCE_OTHER:
                sourceStr = "OTHER";
                break;
            default:
                sourceStr = "UNKNOWN";
                break;
        }

        switch (type) {
            case GL_DEBUG_TYPE_ERROR:
                typeStr = "ERROR";
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                typeStr = "DEPRECATED BEHAVIOR";
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                typeStr = "UNDEFINED BEHAVIOR";
                break;
            case GL_DEBUG_TYPE_PORTABILITY:
                typeStr = "PORTABILITY";
                break;
            case GL_DEBUG_TYPE_PERFORMANCE:
                typeStr = "PERFORMANCE";
                break;
            case GL_DEBUG_TYPE_OTHER:
                typeStr = "OTHER";
                break;
            case GL_DEBUG_TYPE_MARKER:
                typeStr = "MARKER";
                break;
            default:
                typeStr = "UNKNOWN";
                break;
        }

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                severityStr = "HIGH";
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                severityStr = "MEDIUM";
                break;
            case GL_DEBUG_SEVERITY_LOW:
                severityStr = "LOW";
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                severityStr = "NOTIFICATION";
                break;
            default:
                severityStr = "UNKNOWN";
                break;
        }

        fmt::println("[{} {} {} {}] {}", severityStr, sourceStr, typeStr, id, std::string_view{message, static_cast<size_t>(length)});
    }, nullptr);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    GLuint matFbo, matColor, matPos, matDepth;

    glGenTextures(1, &matColor);
    glBindTexture(GL_TEXTURE_2D, matColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, window->w, window->h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenTextures(1, &matPos);
    glBindTexture(GL_TEXTURE_2D, matPos);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32I, window->w, window->h, 0, GL_RGB_INTEGER, GL_INT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenTextures(1, &matDepth);
    glBindTexture(GL_TEXTURE_2D, matDepth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, window->w, window->h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &matFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, matFbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, matColor, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, matPos, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, matDepth, 0);
    GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, drawBuffers);

    GLint fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
        fmt::println("failed to create framebuffer: {:x}", fboStatus);
        glDeleteFramebuffers(1, &matFbo);
        glDeleteTextures(1, &matColor);
        glDeleteTextures(1, &matPos);
        glDeleteTextures(1, &matDepth);
        return fboStatus;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Shader defaultShader;
    defaultShader.compile(DEFAULT_VERT, DEFAULT_FRAG);
    defaultShader.link();
    glUseProgram(defaultShader.program());
    GLint modelLoc = glGetUniformLocation(defaultShader.program(), "model");
    GLint viewLoc = glGetUniformLocation(defaultShader.program(), "view");
    GLint projectionLoc = glGetUniformLocation(defaultShader.program(), "projection");
    GLint colorLoc = glGetUniformLocation(defaultShader.program(), "color");

    Shader matShader;
    matShader.compile(MAT_VERT, MAT_FRAG);
    matShader.link();
    glUseProgram(matShader.program());
    GLint matViewLoc = glGetUniformLocation(matShader.program(), "view");
    GLint matProjectionLoc = glGetUniformLocation(matShader.program(), "projection");
    GLint matColorLoc = glGetUniformLocation(matShader.program(), "matColor");
    GLint matPosLoc = glGetUniformLocation(matShader.program(), "matPos");
    GLint matDepthLoc = glGetUniformLocation(matShader.program(), "matDepth");
    glUniform1i(matColorLoc, 0);
    glUniform1i(matPosLoc, 1);
    glUniform1i(matDepthLoc, 2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, matColor);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, matPos);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, matDepth);

    s_cube.setup();
    s_quad.setup();

    float aspect = static_cast<float>(window->w) / static_cast<float>(window->h);
    glm::mat4 model = 1.0f;
    glm::mat4 projection = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float cameraYaw = 0.0f, cameraPitch = 0.0f;
    bool captured = false;

    glUseProgram(defaultShader.program());
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUseProgram(matShader.program());
    glUniformMatrix4fv(matProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    auto start = asp::Instant::now();
    auto time = 0.0f;

    while (!RGFW_window_shouldClose(window)) {
        RGFW_event event;
        while (RGFW_window_checkEvent(window, &event)) {
            if (event.type == RGFW_quit)
                break;
        }

        auto newTime = start.elapsed().seconds<float>();
        auto dt = newTime - time;
        time = newTime;

        if (RGFW_isKeyPressed(RGFW_return)) {
            captured = !captured;
            RGFW_window_showMouse(window, !captured);
            RGFW_window_captureRawMouse(window, captured);
        }

        if (captured) {
            float dmX, dmY;
            RGFW_getMouseVector(&dmX, &dmY);

            const float cameraSensitivity = 0.3f;
            cameraYaw += dmX * cameraSensitivity;
            cameraPitch -= dmY * cameraSensitivity;

            if (cameraPitch > 89.0f)
              cameraPitch = 89.0f;
            if (cameraPitch < -89.0f)
              cameraPitch = -89.0f;

            glm::vec3 direction;
            direction.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
            direction.y = sin(glm::radians(cameraPitch));
            direction.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
            cameraFront = glm::normalize(direction);

            const float cameraSpeed = RGFW_isKeyDown(RGFW_shiftL) ? 3.0f : 1.0f;
            if (RGFW_isKeyDown(RGFW_w))
                cameraPos += cameraFront * cameraSpeed * dt;
            if (RGFW_isKeyDown(RGFW_s))
                cameraPos -= cameraFront * cameraSpeed * dt;
            if (RGFW_isKeyDown(RGFW_a))
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
            if (RGFW_isKeyDown(RGFW_d))
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
        }

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glUseProgram(defaultShader.program());
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUseProgram(matShader.program());
        glUniformMatrix4fv(matViewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);


        glBindFramebuffer(GL_FRAMEBUFFER, matFbo);
        glViewport(0, 0, window->w, window->h);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(2.0f, -0.5f, 0.0f));
        glUseProgram(defaultShader.program());
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
        s_cube.draw();


        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, window->w, window->h);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model = 1.0f;
        glUseProgram(defaultShader.program());
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(colorLoc, 1.0f, 0.5f, 0.2f, 1.0f);
        s_cube.draw();

        glUseProgram(matShader.program());
        s_quad.draw();


        RGFW_window_swapBuffers_OpenGL(window);
    }

    glDeleteFramebuffers(1, &matFbo);
    glDeleteTextures(1, &matColor);
    glDeleteTextures(1, &matPos);
    glDeleteTextures(1, &matDepth);
    s_cube.cleanup();
    s_quad.cleanup();
    defaultShader.cleanup();
    matShader.cleanup();

    RGFW_window_close(window);
    return 0;
}
