#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace std;
using namespace glm;

// Vertex shader source code
const char* vertexShaderSource = R"(
    #version 330 core

    layout (location = 0) in vec2 position;
    layout (location = 1) in vec3 vertexColor;

    out vec3 color;

    uniform float rotationAngle;
    uniform mat4 rotationMatrix;

    void main()
    {
        vec2 offset = vec2(0.5, 0.0); // Offset to center the pattern
        float angle = rotationAngle + atan(position.y - offset.y, position.x - offset.x);
        float radius = length(position - offset);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        gl_Position = rotationMatrix * vec4(x + offset.x, y + offset.y, 0.0, 1.0);
        color = vertexColor;
    }
)";

// Fragment shader source code
const char* fragmentShaderSource = R"(
    #version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;


void main()
{
	FragColor = vec4(color, 1.0f);
}
)";


int main()
{
    const int NUM_SEGMENTS = 180;

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 800, "Newton Disc", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load GLAD
    if (!gladLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Vertex shader compilation failed: " << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Fragment shader compilation failed: " << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Shader program linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
    std::vector<GLuint> indices;

    float radius = 0.5f;

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    colors.push_back(1.0f);
    colors.push_back(1.0f);
    colors.push_back(1.0f);

    for (int i = 0; i <= NUM_SEGMENTS; ++i)
    {
        float angle = 2.0f * 3.1416 * i / NUM_SEGMENTS;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        vertices.push_back(x);
        vertices.push_back(y);

        float hue = angle / (2.0 * 3.1416) ;
        int region = int(hue * 7);
        float red = 0.0f, green = 0.0f, blue = 0.0f;

        switch (region)
        {
            case 0: red = 0.0f; green = 1.0f; blue = 1.0f; break;
            case 1: red = 1.0f; green = 0.0f; blue = 0.0f; break;
            case 2: red = 255.f / 255.f; green = 165.f / 255.f; blue = 79.f / 255.f; break;
            case 3: red = 1.0f; green = 1.0f; blue = 0.0f; break;
            case 4: red = 0.0f; green = 1.0f; blue = 0.0f; break;
            case 5: red = 0.0f; green = 0.0f; blue = 1.0f; break;
            case 6: red = 1.0f; green = 0.0f; blue = 1.0f; break;
        }

        colors.push_back(red);
        colors.push_back(green);
        colors.push_back(blue);
    }

    // Circle indices
    for (int i = 1; i <= NUM_SEGMENTS; ++i)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    float rotationSpeed = 0.1f; 
    float acceleration = 1.01f;
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        float rotationAngle = rotationSpeed ;
        
        
        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        glm::mat4 rotationMatrix = glm::mat4(1.0f);
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap buffers and poll events
        rotationSpeed *= acceleration;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up resources
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
