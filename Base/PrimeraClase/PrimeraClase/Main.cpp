#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* insideVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";

const char* insideFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.9922f, 0.9052f, 0.298f, 1.0f);\n"
"}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apuntador de refrencia a la ventana que se usara en la gpu
    GLFWwindow* window = glfwCreateWindow(800, 800, "test", NULL, NULL);

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

    glfwMakeContextCurrent(window);
    gladLoadGL();

    //se crean shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint insideVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(insideVertexShader, 1, &insideVertexShaderSource, NULL);
    glCompileShader(insideVertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint insideFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(insideFragmentShader, 1, &insideFragmentShaderSource, NULL);
    glCompileShader(insideFragmentShader);

    //se crea un programa donde se guardan los shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLuint insideShaderProgram = glCreateProgram();
    glAttachShader(insideShaderProgram, insideVertexShader);
    glAttachShader(insideShaderProgram, insideFragmentShader);
    glLinkProgram(insideShaderProgram);

    //Se eliminan los shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(insideVertexShader);
    glDeleteShader(insideFragmentShader);


    //se almacena y renderiza la infromacion en la gpu
    GLuint VAO, VBO;
    GLuint EBO;

    GLuint InsideVAO, InsideVBO;
    GLuint InsideEBO;


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &InsideVAO);
    glGenBuffers(1, &InsideVBO);
    glGenBuffers(1, &InsideEBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




    glBindVertexArray(InsideVAO);

    glBindBuffer(GL_ARRAY_BUFFER, InsideVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(insideVertex), insideVertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, InsideEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(insideIndex), insideIndex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glViewport(0, 0, 800, 800);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5255f, 0.8706f, 0.4471, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glUseProgram(insideShaderProgram);
        glBindVertexArray(InsideVAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    //limpia el buffer para liberar la gpu
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &InsideVAO);
    glDeleteBuffers(1, &InsideVBO);
    glDeleteBuffers(1, &InsideEBO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(insideShaderProgram);

    glfwTerminate();
}