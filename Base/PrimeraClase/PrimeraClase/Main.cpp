#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

    GLFWwindow* GWindow = glfwCreateWindow(800,800,"Main Window", NULL, NULL);

    //Se debe agregar el contexto de OpenGL. Cada ventana GLFW tiene su propio contexto. 
    glfwMakeContextCurrent(GWindow);

    //Mientras no se cierre la ventana, lee los eventos. Se debe mantener viva la ventana. 
    while (!glfwWindowShouldClose(GWindow))
    {
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}