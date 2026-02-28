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
#include <defaultText.frag.h>

#include <quad.vert.h>
#include <quad.frag.h>

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

    GLuint textFbo, textChar, textDepth;

    glGenTextures(1, &textChar);
    glBindTexture(GL_TEXTURE_2D, textChar);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8UI, window->w / 8, window->h / 8, 0, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenTextures(1, &textDepth);
    glBindTexture(GL_TEXTURE_2D, textDepth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, window->w / 8, window->h / 8, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &textFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, textFbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textChar, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textDepth, 0);

    GLint fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
        fmt::println("failed to create framebuffer: {}", fboStatus);
        return -1;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Shader defaultShader;
    defaultShader.compile(DEFAULT_VERT, DEFAULT_FRAG);
    defaultShader.link();
    glUseProgram(defaultShader.program());
    GLint defaultModelLoc = glGetUniformLocation(defaultShader.program(), "model");
    GLint defaultViewLoc = glGetUniformLocation(defaultShader.program(), "view");
    GLint defaultProjectionLoc = glGetUniformLocation(defaultShader.program(), "projection");

    Shader defaultTextShader;
    defaultTextShader.compile(DEFAULT_VERT, DEFAULTTEXT_FRAG);
    defaultTextShader.link();
    glUseProgram(defaultTextShader.program());
    GLint defaultTextModelLoc = glGetUniformLocation(defaultTextShader.program(), "model");
    GLint defaultTextViewLoc = glGetUniformLocation(defaultTextShader.program(), "view");
    GLint defaultTextProjectionLoc = glGetUniformLocation(defaultTextShader.program(), "projection");
    GLint defaultTextChLoc = glGetUniformLocation(defaultTextShader.program(), "ch");

    Shader quadShader;
    quadShader.compile(QUAD_VERT, QUAD_FRAG);
    quadShader.link();
    glUseProgram(quadShader.program());
    GLint quadTextCharLoc = glGetUniformLocation(quadShader.program(), "textChar");
    GLint quadTextDepthLoc = glGetUniformLocation(quadShader.program(), "textDepth");
    glUniform1i(quadTextCharLoc, 0);
    glUniform1i(quadTextDepthLoc, 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textChar);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textDepth);

    s_cube.setup();
    s_quad.setup();

    float aspect = static_cast<float>(window->w) / static_cast<float>(window->h);
    glm::mat4 projection = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float cameraYaw = 0.0f, cameraPitch = 0.0f;
    bool captured = false;

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

        glBindFramebuffer(GL_FRAMEBUFFER, textFbo);
        glViewport(0, 0, window->w / 8, window->h / 8);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);

        glm::mat4 model = 1.0f;
        //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(2.0f, -0.5f, 0.0f));

        glUseProgram(defaultTextShader.program());
        glUniformMatrix4fv(defaultTextModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(defaultTextViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(defaultTextProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform1ui(defaultTextChLoc, '#');
        s_cube.draw();

        glUniform1ui(defaultTextChLoc, '+');
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        s_cube.draw();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, window->w, window->h);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        model = 1.0f;

        glUseProgram(defaultShader.program());
        glUniformMatrix4fv(defaultModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(defaultViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(defaultProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        s_cube.draw();

        glUseProgram(quadShader.program());

        s_quad.draw();

        RGFW_window_swapBuffers_OpenGL(window);
    }

    glDeleteFramebuffers(1, &textFbo);
    glDeleteTextures(1, &textChar);
    glDeleteTextures(1, &textDepth);
    s_cube.cleanup();
    s_quad.cleanup();
    defaultShader.cleanup();
    defaultTextShader.cleanup();
    quadShader.cleanup();

    RGFW_window_close(window);
    return 0;
}
