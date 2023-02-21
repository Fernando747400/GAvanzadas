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

    gladLoadGL();
    glViewport(0,0,800,800);//Coordenadas de la ventana viewport
    glClearColor(.3, .2, .8, 0); //Color en 0 - 1
    glClear(GL_COLOR_BUFFER_BIT); //Limpia el viewport 
    glfwSwapBuffers(GWindow); 

    //Mientras no se cierre la ventana, lee los eventos. Se debe mantener viva la ventana. 
    while (!glfwWindowShouldClose(GWindow))
    {
        glfwPollEvents();
    }

    //Destruye la ventana
    glfwDestroyWindow(GWindow);

    glfwTerminate();
    return 0;
}