#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

    GLFWwindow* GWindow = glfwCreateWindow(800,800,"Main Window", NULL, NULL);

    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };

    //Se debe agregar el contexto de OpenGL. Cada ventana GLFW tiene su propio contexto. 
    glfwMakeContextCurrent(GWindow);
    gladLoadGL();
    

#pragma region Shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);  //Shader = new shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram(); //Se agrupan los shaders en uno solo
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader); //Se eliminan los shaders
    glDeleteShader(fragmentShader);
#pragma endregion

#pragma region CpuToGpu
    GLuint VAO, VBO;

    //Almacenado y renderizado en la memoria del GPU

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
#pragma endregion


     
    glViewport(0,0,800,800);//Coordenadas de la ventana viewport
    glClearColor(.3, .2, .8, 0); //Color en 0 - 1
    glClear(GL_COLOR_BUFFER_BIT); //Limpia el viewport 
    glfwSwapBuffers(GWindow); 

    //Mientras no se cierre la ventana, lee los eventos. Se debe mantener viva la ventana. 
    while (!glfwWindowShouldClose(GWindow))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(GWindow);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);//Se libera el buffer usado anteriormente
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    //Destruye la ventana
    glfwDestroyWindow(GWindow);

    glfwTerminate();
    return 0;
}