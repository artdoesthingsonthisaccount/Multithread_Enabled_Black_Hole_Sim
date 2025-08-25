#include <cstdio>
#include <iostream>

// Include order matters: GLEW before GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static const char* glErrName(GLenum e) {
    switch (e) {
        case GL_NO_ERROR: return "GL_NO_ERROR";
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        default: return "(unknown)";
    }
}

static bool try_context_and_glew(int maj, int min, int profile /*0:any,1:core,2:compat*/) {
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    if (maj > 0) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
    }
    if (profile == 1) glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (profile == 2) glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* win = glfwCreateWindow(800, 600, "GLEW probe", nullptr, nullptr);
    if (!win) {
        std::cerr << "  createWindow failed for "
                  << (maj? std::to_string(maj)+"."+std::to_string(min):"ANY")
                  << (profile==1?" core": profile==2?" compat":" any")
                  << "\n";
        return false;
    }

    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    // Check GL strings *before* GLEW
    const GLubyte* ver = glGetString(GL_VERSION);
    const GLubyte* ven = glGetString(GL_VENDOR);
    const GLubyte* ren = glGetString(GL_RENDERER);
    std::cout << "  GL_VERSION : " << (ver ? reinterpret_cast<const char*>(ver) : "(null)") << "\n";
    std::cout << "  GL_VENDOR  : " << (ven ? reinterpret_cast<const char*>(ven) : "(null)") << "\n";
    std::cout << "  GL_RENDERER: " << (ren ? reinterpret_cast<const char*>(ren) : "(null)") << "\n";

    // Clear any spurious error
    while (GLenum e = glGetError()) {
        std::cout << "  pre-glew GL error cleared: " << glErrName(e) << "\n";
    }

    glewExperimental = GL_TRUE; // necessary for core/modern paths
    GLenum gerr = glewInit();
    if (gerr != GLEW_OK) {
        std::cerr << "  GLEW init failed: " << glewGetErrorString(gerr) << "\n";
        glfwDestroyWindow(win);
        return false;
    }

    // Some drivers set an error during GLEW init—clear & log once
    GLenum post = glGetError();
    if (post != GL_NO_ERROR) {
        std::cout << "  post-glew GL error (benign): " << glErrName(post) << "\n";
    }

    // Show something and present so the window actually appears
    int w,h; glfwGetFramebufferSize(win, &w, &h);
    glViewport(0,0,w,h);
    glClearColor(0.1f,0.15f,0.25f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(win);

    // Quit on Esc
    glfwSetKeyCallback(win, [](GLFWwindow* w, int key, int, int action, int){
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(w, 1);
    });

    // Short loop so you can see the window
    double t0 = glfwGetTime();
    while (!glfwWindowShouldClose(win) && glfwGetTime() - t0 < 2.0) {
        glfwPollEvents();
    }

    glfwDestroyWindow(win);
    return true;
}

int main() {
    glfwSetErrorCallback([](int code, const char* desc){
        fprintf(stderr, "GLFW error %d: %s\n", code, desc);
    });

    if (!glfwInit()) {
        std::cerr << "GLFW init failed (no display/session?)\n";
        return 1;
    }

    std::cout << "Trying 3.3 core...\n";
    if (try_context_and_glew(3,3,1)) { glfwTerminate(); return 0; }

    std::cout << "Trying 3.3 compat...\n";
    if (try_context_and_glew(3,3,2)) { glfwTerminate(); return 0; }

    std::cout << "Trying ANY profile/version...\n";
    if (try_context_and_glew(0,0,0)) { glfwTerminate(); return 0; }

    std::cerr << "All attempts failed.\n";
    glfwTerminate();
    return 2;
}
