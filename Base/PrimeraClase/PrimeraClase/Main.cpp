#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

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

float randomFloat()
{
    return (float)(rand()) / (float)(RAND_MAX);
}

float GetAbsTime() {
    float time = 1.2f + 0.4f * abs(sin(glfwGetTime()));
	return time;
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
    GLfloat squareVertices[] =
    {
     -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
     -0.5f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f
    };

    GLuint squareIndices[] =
    {
     0, 2, 1,
     0, 3, 2
    };

#pragma endregion


    glfwMakeContextCurrent(window);
    gladLoadGL();

    //Shader _shaderProgram("default.vert", "default.frag");
    Shader _shaderOutside("triforce.vert", "rainbow.frag");
    Shader _shaderInside("triforceinside.vert","rainbow.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(squareVertices, sizeof(squareVertices));
    EBO EBO1(squareIndices, sizeof(squareIndices));
    
    VAO1.LinkAttributes(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttributes(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint _outsideScale = glGetUniformLocation(_shaderOutside.ID, "scale");
    GLuint _outsideColorOffset = glGetUniformLocation(_shaderOutside.ID, "offsetColor");

    glViewport(0, 0, 1000, 1000);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.901f, 0.313f, 0.431f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        _shaderOutside.Activate();
        glUniform1f(_outsideScale, GetNegativeScale(0.8f, 0.2f));
        glUniform1f(_outsideColorOffset, GetAbsTime());
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    //limpia el buffer para liberar la gpu
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    _shaderOutside.Delete();
    _shaderInside.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}