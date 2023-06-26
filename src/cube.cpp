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

/*#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;

// Outputs the color for the Fragment Shader
out vec3 color;

// Controls the scale of the vertices
uniform mat4 scale;
// Uniform color variable

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    // Outputs the positions/coordinates of all vertices
    gl_Position = proj*view* scale * vec4(aPos, 1.0);
    // Assigns the colors from the Vertex Data to "color"
    color =  aColor;
}*/
GLfloat vertices[] = {

    -0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f,   
    0.25f, -0.25f, 0.25f,  1.0f, 1.0f, 1.0f,    
    0.25f, 0.25f, 0.25f,  1.0f, 1.0f, 1.0f,     
    -0.25f, 0.25f, 0.25f,  1.0f, 1.0f, 1.0f,     


    -0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 0.0f,   
    0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 0.0f,    
    0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 0.0f,     
    -0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 0.0f,    

    -0.25f, -0.25f, -0.25f, 0.0f, 0.0f, 1.0f,   
    -0.25f, -0.25f, 0.25f, 0.0f, 0.0f, 1.0f,    
    -0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 1.0f,    
    -0.25f, 0.25f, -0.25f, 0.0f, 0.0f, 1.0f,    


    0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 1.0f,    
    0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 1.0f,    
    0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 1.0f,     
    0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 1.0f,     


    -0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 0.0f,     
    0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 0.0f,      
    0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f,     
    -0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f,   

   
    -0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f,    
    0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f,     
    0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f,    
    -0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f,   
};


GLuint indices[] = {

    8, 9, 10,
    10, 11, 8,


    12, 13, 14,
    14, 15, 12,

    16, 17, 18,
    18, 19, 16,

    20, 21, 22,
    22, 23, 20,
    6, 7, 4,
    4, 5, 6,
    0, 1, 2,
    2, 3, 0
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
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	
	
	
  float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;


	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


  glEnable(GL_DEPTH_TEST);  
	while (!glfwWindowShouldClose(window))
{
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        rotationX += 5.0f;
    }

     if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        rotationY += 5.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        rotationZ += 5.0f;
    }
    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   
    shaderProgram.Activate();
    VAO1.Bind();
    // Bind the VAO so OpenGL knows to use it
    double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}
      
    glm::mat4 transform = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
    view = glm::translate(view, glm::vec3(0.0f, -0.0f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)800.0f / 800.0f, 0.1f, 100.0f);
    int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    //transform3 = glm::translate(transform3, (glm::vec3(+0.25f, 0.25f, -0.25f))); 
    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform));
    glUniform1f(uniID, 0.5f);
    
    //GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
    float time3 = glfwGetTime() * 45 ;

    float time = glfwGetTime();
    float scaleFactor1 = 0.35f + sin(time) * 0.3f; 
    float scaleFactor2 = 0.65f + sin(time) * 0.7f; 
    
    // Tell OpenGL which Shader Program we want to use


    // ...
    /*glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)8000 / 8000, 0.1f, 100.0f);

		// Outputs the matrices into the Vertex Shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
*/
		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		//glUniform1f(uniID, 0.5f);
    // Apply rotations
   
   
   

  
    /*float time3 = glfwGetTime() * 45 ;
	//glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, -0.0f, 0.0f));
   
    //glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform2));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(float)));
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glm::mat4 transform3 = glm::mat4(1.0f);
    transform3 = glm::translate(transform3, -(glm::vec3(+0.6f, -0.6f,0.0f)));  
    transform3 = glm::rotate(transform3, glm::radians(time3), glm::vec3( 0.0f,0.0f,1.0f));
    transform3 = glm::translate(transform3, (glm::vec3(+0.6f, -0.6f, 0.0f))); 
    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform3));
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(24 * sizeof(float)));
    // Swap the back buffer with the front buffer
    //renderCircle();*/
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
