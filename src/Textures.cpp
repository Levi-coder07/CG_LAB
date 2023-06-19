#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "stb_image.h"

GLfloat vertices[] = {
    
     0.25f,  0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 
     0.25f, -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -0.25f, -0.25f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
    -0.25f,  0.25f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 

     0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 
     0.5f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 
    1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
    1.0f,  -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f , 

     -0.58f,  0.15f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 
    - 0.58f, -0.15f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 
    -0.88f, -0.15f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
   - 0.88f,  0.15f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  
};
GLuint indices[] = {
    // Instance 1
    0, 1, 3, // first triangle
    1, 2, 3, // second triangle

    // Instance 2
    4, 5, 7, // first triangle
    5, 6, 7,  // second triangle
    8, 9, 11, // first triangle
    9, 10, 11  //
};
void drawLines(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    // Set the color of the lines
    glColor3f(r, g, b);

    // Draw the first line
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}
int main()
{
	// Initialize GLFW
	glfwInit();
    
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "OpenGL", NULL, NULL);
	// Error check if the window fails to create

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	//glViewport(0, 0, 800, 800);
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

    drawLines(0, 0, 800, 0, 1.0f, 0.0f, 0.0f);
    drawLines(0, 0, 0, 800, 0.0f, 1.0f, 0.0f);
    drawLines(0, 800 / 3, 800, 800 / 3, 0.0f, 0.0f, 1.0f);


	// Generates Shader object using shaders defualt.vert and default.frag
   
	Shader shaderProgram("C:\\Users\\Levi\\Downloads\\MyProject\\src\\default.vert", "C:\\Users\\Levi\\Downloads\\MyProject\\src\\default.frag");



	// Generates Vertex Array Object and binds it
    
	VAO VAO1;
    
	VAO1.Bind();
    
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
     
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load("C:\\Users\\Levi\\Downloads\\MyProject\\src\\image1.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
   
	 bool reverseDirection = false;
     float translationSpeed = 0.50f;
    const float translationLimit =1.5f;
	// Main while loop
    float previousTime = glfwGetTime();
    float translationY = 0.0f;
    //initializeCircle(0.0f, 0.0f, 0.2f);
    float rotationAngle = 0.0f;
    float scaleFactor = 1.0f;
	while (!glfwWindowShouldClose(window))
{
    // Specify the color of the background
    glClearColor(0.07f, 0.125f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    float time = glfwGetTime();
    glClear(GL_COLOR_BUFFER_BIT);
    
    shaderProgram.Activate();
    // Bind the VAO so OpenGL knows to use it
    VAO1.Bind();


    //scaleFactor -= 0.005f;

    float scaleFactor1 = 0.30f + sin(time) * 0.33f;
    //scaleFactor = glm::max(scaleFactor, 0.0f);

    // Calculate the translation vector to the center point
    

    // Apply the scaling and translation transformations1
    glm::mat4 transform =glm::scale(glm::mat4(1.0f) ,glm::vec3(scaleFactor1));
   
    
  

    // Pass the transformation matrix to the shader
    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform));

    // Draw the figure
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
     float time3 = glfwGetTime() * 45 ;
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    translationY += deltaTime * translationSpeed;
  
    if (translationY >= translationLimit || translationY <= (-translationLimit +1.5f)) {
        
        
        translationSpeed = -translationSpeed;
    }

    
    if (reverseDirection)
        translationY = -translationY;

    glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, translationY, 0.0f));
    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform2));
     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(float)));
    glm::mat4 transform3 = glm::mat4(1.0f);
    transform3 = glm::translate(transform3, -(glm::vec3(+ 0.58f,  -0.15f, 0.0f)));  
    transform3 = glm::rotate(transform3, glm::radians(-time3), glm::vec3( 0.0f,0.0f,1.0f));
    transform3 = glm::translate(transform3, (glm::vec3(+0.58f, - 0.15f, 0.0f))); 
    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform3));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(float)));
    
    glfwSwapBuffers(window);
    // Take care of all GLFW events
    glfwPollEvents();
}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
