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


// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.25f, -0.0f * float(sqrt(3)) * 1 / 3, 0.0f,     0.1f, 0.1f,  0.1f, // Lower left corner
	 0.75f, -0.0f * float(sqrt(3)) * 1 / 3, 0.0f,     0.0f, 0.1f, 0.1f, // Lower right corner
	 0.25f,  0.75f * float(sqrt(3)) * 2 / 3, 0.0f,      0.0f, 0.1f, 0.1f, // Upper corner
	0.0f, 1.50f * float(sqrt(3)) * 1 / 6, 0.0f,     0.0f, 0.1f, 0.1f, // Inner left
	 0.5f, 1.50f * float(sqrt(3)) * 1 / 6, 0.0f,     0.0f, 0.1f, 0.1f, // Inner right
	 0.25f, -0.0f * float(sqrt(3)) * 1 / 3, 0.0f,     0.94f, 0.82f, 0.86f,// Inner down
     -0.50f, 1.50f * float(sqrt(3)) * 1 / 6, 0.0f,    0.97, 0.93, 0.46,//
      0.75f, 1.50f * float(sqrt(3)) * 1 / 6, 0.0f,     0.5f, 1.0f, 1.0f,
      -0.25f, -1.5f * float(sqrt(3)) * 1 / 6, 0.0f,      0.0f, 0.1f, 0.1f,
      0.25f, -1.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.0f, 0.1f, 0.1f,
      -0.75f, -1.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.96f, 0.33f, 0.44f,
      0.75f, -1.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.0f, 1.0f, 0.0f,
       0.0f,  -0.75f * float(sqrt(3)) * 2 / 3, 0.0f,     0.61f, 0.69f, 0.85f
};

// Indices for vertices order
GLuint indices[] =
{
	6,3,0,
	4,5,1
};



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
	glViewport(0, 0, 800, 800);



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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		 float time = glfwGetTime();
		float scaleFactor1 = 0.65f + sin(time) * 0.6f; // Scale factor for the first triangle
		float scaleFactor2 = 0.65f + sin(time) * 0.7f; // Scale factor for the second triangle
		glm::vec3 changingColor(scaleFactor1, scaleFactor2 , scaleFactor2);

// Get the location of the "baseColor" uniform
		GLint baseColorLoc = glGetUniformLocation(shaderProgram.ID, "baseColor");
		// Set the value of the "baseColor" uniform
		glUniform3fv(baseColorLoc, 1, glm::value_ptr(changingColor));
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		VAO1.Bind();

		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor1));
		glm::mat4 transform2 = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor2));
        // Assign transformation matrix to the uniform
        glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform));
		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		
		// Bind the VAO so OpenGL knows to use it
		
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,(void*)0);
		glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform2));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,(void*)(3 * sizeof(float)));
        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		// Swap the back buffer with the front buffer
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