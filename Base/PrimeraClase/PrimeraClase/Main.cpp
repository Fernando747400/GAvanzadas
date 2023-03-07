#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


//A method that return a float that scales with SIN +- 20% of original size
float GetScale(float baseScale, float percentageDifference)
{
	float scale = baseScale + percentageDifference * sin(glfwGetTime());
	return scale;
}

float GetNegativeScale(float baseScale, float percentageDifference)
{
    float scale = baseScale + percentageDifference * -sin(glfwGetTime());
    return scale;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apuntador de refrencia a la ventana que se usara en la gpu
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "test", NULL, NULL);

#pragma region Verts
    GLfloat vertices[] =
    {
         -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,       // Esquina inferior izq
         0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,        // Esquina inferior derecha
         0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   // Esquina superior
         -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,      // Interior izquierda
         0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,    // Interior derecha
         0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f        // Interior abajo
    };

    GLfloat insideVertex[] =
    {
         -0.45f, -0.45f * float(sqrt(3)) / 3, 0.0f,       // Esquina inferior izq
         -0.5f / 2, 0.5f * float(sqrt(1.5f)) / 6, 0.0f,      // Interior izquierda
         -0.05f, -0.45f * float(sqrt(3)) / 3, 0.0f,        // Interior abajo


         0.05f, -0.45f * float(sqrt(3)) / 3, 0.0f,        // Interior abajo
         0.45f, -0.45f * float(sqrt(3)) / 3, 0.0f,        // Esquina inferior derecha
         0.5f / 2, 0.5f * float(sqrt(1.5f)) / 6, 0.0f,   // Esquina superior

         -0.4f / 2, 0.6f * float(sqrt(3)) / 6, 0.0f,      // Interior izquierda
         0.0f, 0.45f * float(sqrt(3)) * 2 / 3, 0.0f,   // Esquina superior
         0.4f / 2, 0.6f * float(sqrt(3)) / 6, 0.0f,    // Interior derecha
    };

    GLuint indices[] =
    {
    0, 3, 5, // Triangulo inferior izq
    3, 2, 4, // Triangulo inferior der
    5, 4, 1 // Triangulo superior
    };

    GLuint insideIndex[] =
    {
    0, 1, 2, // Triangulo inferior izq
    3, 4, 5, // Triangulo inferior der
    6, 7, 8 // Triangulo superior
    };
#pragma endregion


    glfwMakeContextCurrent(window);
    gladLoadGL();

    //Shader _shaderProgram("default.vert", "default.frag");
    Shader _shaderOutside("triforce.vert", "black.frag");
    Shader _shaderInside("triforceinside.vert","yellow.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint _outsideScale = glGetUniformLocation(_shaderOutside.ID, "scale");

    VAO VAO2;
    VAO2.Bind();

    VBO VBO2(insideVertex, sizeof(insideVertex));
    EBO EBO2(insideIndex, sizeof(insideIndex));

    VAO2.LinkVBO(VBO2, 0);

    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();

    GLuint _insideScale = glGetUniformLocation(_shaderInside.ID, "scale");

    glViewport(0, 0, 1000, 1000);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5255f, 0.8706f, 0.4471, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        _shaderOutside.Activate();
        glUniform1f(_outsideScale, GetNegativeScale(0.8f, 0.2f));
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        _shaderInside.Activate();
        glUniform1f(_insideScale, GetScale(1.0f, 0.2f));
        VAO2.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);    

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    //limpia el buffer para liberar la gpu
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    VAO2.Delete();
    VBO2.Delete();
    EBO2.Delete();

    _shaderOutside.Delete();
    _shaderInside.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}