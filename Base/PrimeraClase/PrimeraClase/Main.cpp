#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

#pragma region MyMethods
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
#pragma endregion


int main()
{  
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apuntador de refrencia a la ventana que se usara en la gpu
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "test", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();

#pragma region ImageTexture
    int widthTx, heightTx, numCol;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("Cat.png", &widthTx, &heightTx, &numCol, 0);

    std::cout << numCol << std::endl;

    GLuint texture;
    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTx, heightTx, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
#pragma endregion

#pragma region Verts
    GLfloat squareVertices[] =
    {
     -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     -0.5f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
     0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   1.0f, 0.0f
    };

    GLuint squareIndices[] =
    {
     0, 2, 1,
     0, 3, 2
    };

#pragma endregion

    Shader _textureShader("Texture.vert", "Texture.frag");

    VAO VAO1;
    glBindTexture(GL_TEXTURE_2D, texture);
    VAO1.Bind();

    VBO VBO1(squareVertices, sizeof(squareVertices));
    EBO EBO1(squareIndices, sizeof(squareIndices));
    

    VAO1.LinkAttributes(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttributes(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttributes(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint tex0uni = glGetUniformLocation(_textureShader.ID, "tex0");

    _textureShader.Activate();
    glUniform1i(tex0uni, 0);

    glViewport(0, 0, 1000, 1000);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.901f, 0.313f, 0.431f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, texture); // not sure if this goes here

        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //Esto es un comentario
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //limpia el buffer para liberar la gpu
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    _textureShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}