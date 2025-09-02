#include <cstdio>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//export line:
//export LIBDECOR_PLUGIN_DIR=/usr/lib/x86_64-linux-gnu/libdecor/plugins-1
//contains libdecor-gtk.so

int main(){

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);//FIX: because GLEW doesn't work on wayland for some reason
    if (!glfwInit()){
        std::cerr <<"failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * win = glfwCreateWindow(1920,1080, "BH_sim", NULL, NULL);
    if (!win){
        std::cerr << "failed to create glfw window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    glewExperimental = GL_TRUE;

    GLenum err = glewInit();
    std::cout << "GL_VENDOR: "   << glGetString(GL_VENDOR)   << std::endl;
    std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GL_VERSION: "  << glGetString(GL_VERSION)  << std::endl;

    if (err != GLEW_OK){
        std::cerr << "failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    while (!glfwWindowShouldClose(win)){
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;

}