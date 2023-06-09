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

// Vertices coordinates
/*GLfloat vertices[] =
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
};*/
GLfloat vertices[] = {
    // COORDINATES                  /     COLORS           
    // Roof
	
    -0.25f, -0.05f * float(sqrt(3)), 0.0f,     0.9f, 0.2f, 0.2f, // Bottom left
    0.25f, -0.05f * float(sqrt(3)), 0.0f,      0.9f, 0.2f, 0.2f, // Bottom right
    0.0f, 0.25f * float(sqrt(3)), 0.0f,        0.9f, 0.2f, 0.2f, // Top

   
    -0.25f, -0.05f * float(sqrt(3)), 0.0f,     0.2f, 0.8f, 0.2f, // Bottom left
    0.25f, -0.05f * float(sqrt(3)), 0.0f,      0.2f, 0.8f, 0.2f, // Bottom right
    -0.25f, -0.2f * float(sqrt(3)), 0.0f,      0.2f, 0.8f, 0.2f, // Top left

    -0.25f, -0.2f * float(sqrt(3)), 0.0f,      0.2f, 0.8f, 0.2f, // Top left
    0.25f, -0.05f * float(sqrt(3)), 0.0f,      0.2f, 0.8f, 0.2f, // Bottom right
    0.25f, -0.2f * float(sqrt(3)), 0.0f,       0.2f, 0.8f, 0.2f, // Top right

    -0.075f, -0.2f * float(sqrt(3)), 0.0f,    0.5f, 0.5f, 0.8f, // Bottom left
    0.075f, -0.2f * float(sqrt(3)), 0.0f,     0.5f, 0.5f, 0.8f, // Bottom right
    -0.075f, -0.125f * float(sqrt(3)), 0.0f,  0.5f, 0.5f, 0.8f, // Top left

    -0.075f, -0.125f * float(sqrt(3)), 0.0f,  0.5f, 0.5f, 0.8f, // Top left
    0.075f, -0.2f * float(sqrt(3)), 0.0f,     0.5f, 0.5f, 0.8f, // Bottom right
    0.075f, -0.125f * float(sqrt(3)), 0.0f,   0.5f, 0.5f, 0.8f,
	 -0.15f, 0.0f, 0.0f,                        0.4f, 0.4f, 0.4f, 
    0.15f, 0.0f, 0.0f,                         0.4f, 0.4f, 0.4f, 
    0.0f, 0.2f * float(sqrt(3)), 0.0f,          0.4f, 0.4f, 0.4f,
	  0.6f, -0.2f * float(sqrt(3)), 0.0f,       0.36f, 0.25f, 0.2f, // Bottom right
  0.8f, -0.2f * float(sqrt(3)), 0.0f,       0.36f, 0.25f, 0.2f, // Bottom left
  0.7f, 0.0f * float(sqrt(3)), 0.0f,        0.36f, 0.25f, 0.2f, // Top
0.6f, 0.0f * float(sqrt(3)), 0.0f,       0.4f, 0.4f, 0.0f, // Bottom right
  0.8f, 0.0f * float(sqrt(3)), 0.0f,       0.4f, 0.4f, 0.0f, // Bottom left
  0.7f, 0.15f * float(sqrt(3)), 0.0f,        0.4f, 0.4f, 0.0f, // Top
  

        -0.8f, 0.6f, 0.0f,                       0.9f, 0.2f, 0.2f, // Bottom left
        -0.6f, 0.6f, 0.0f,                       0.9f, 0.2f, 0.2f, // Bottom right
        -0.7f, 0.8f, 0.0f,                       0.9f, 0.2f, 0.2f, // Top

    
        -0.8f, 0.6f, 0.0f,                       0.9f, 0.2f, 0.2f, // Bottom left
        -0.7f, 0.4f, 0.0f,                       0.9f, 0.2f, 0.2f, // Top left
        -0.7f, 0.8f, 0.0f,                       0.9f, 0.2f, 0.2f, // Center

     
        -0.6f, 0.6f, 0.0f,                       0.9f, 0.2f, 0.2f, // Bottom right
        -0.7f, 0.4f, 0.0f,                       0.9f, 0.2f, 0.2f, // Top right
        -0.7f, 0.8f, 0.0f,                       0.9f, 0.2f, 0.2f, // Center

       
        -0.7f, 0.4f, 0.0f,                       0.2f, 0.8f, 0.2f, // Bottom left
        -0.75f, 0.35f, 0.0f,                     0.2f, 0.8f, 0.2f, // Top left
        -0.65f, 0.35f, 0.0f,                     0.2f, 0.8f, 0.2f, 

        
        -0.7f, 0.35f, 0.0f,                      0.5f, 0.5f, 0.8f, 
        -0.75f, 0.35f, 0.0f,                     0.5f, 0.5f, 0.8f, 
        -0.7f, 0.3f, 0.0f,                       0.5f, 0.5f, 0.8f, 

        -0.7f, 0.35f, 0.0f,                      0.5f, 0.5f, 0.8f, 
        -0.65f, 0.35f, 0.0f,                     0.5f, 0.5f, 0.8f, 
        -0.7f, 0.3f, 0.0f,                       0.5f, 0.5f, 0.8f,
        
    
};
// Indices for vertices order
GLuint indices[] = {
    // Roof
    0, 1, 2,

    // Base
    3, 4, 5,
    6, 7, 8,

    // Door
    9, 10, 11,
    12, 13, 14,
	15,16,17,
	18,19,20,
	21,22,23,
    24,25,26,
    27,28,29,
    30,31,32,
    33,34,35,
    36,37,38,
    39,40,41
};

/*GLuint indices[] =
{
	6,3,0,
	4,5,1
};*/
/*GLuint vbo;
GLuint vao;
const int CIRCLE_SEGMENTS = 100;
const float PI = 3.14159265359f;
void initializeCircle(float centerX, float centerY, float radius)
{
    std::vector<float> vertices2;
    float posX = -0.9f;
    float posY = 0.9f;
    // Calculate the vertices of the circle
    for (int i = 0; i < CIRCLE_SEGMENTS; ++i) {
        float theta = 2.0f * PI * float(i) / float(CIRCLE_SEGMENTS);
        float x = radius * std::cos(theta) + posX;
        float y = radius * std::sin(theta) + posY;

        vertices2.push_back(centerX + x);
        vertices2.push_back(centerY + y);
    }

    // Create and bind a vertex buffer object (VBO)
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Upload vertex data to the VBO
    glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), vertices2.data(), GL_STATIC_DRAW);

    // Create and bind a vertex array object (VAO)
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Enable and configure the vertex attribute array
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Render the circle
void renderCircle()
{
    // Bind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);

    // Render the circle
    glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_SEGMENTS);

    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
*/
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
   
	 bool reverseDirection = false;
     float translationSpeed = 0.3f;
    const float translationLimit = 0.2f;
	// Main while loop
    float previousTime = glfwGetTime();
    float translationX = 0.0f;
    //initializeCircle(0.0f, 0.0f, 0.2f);
    float rotationAngle = 0.0f;
	while (!glfwWindowShouldClose(window))
{
    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
     


    float time = glfwGetTime();
    float scaleFactor1 = 0.35f + sin(time) * 0.3f; // Scale factor for the first triangle
    float scaleFactor2 = 0.65f + sin(time) * 0.7f; // Scale factor for the second triangle
    glm::vec3 changingColor(scaleFactor1, scaleFactor2 , scaleFactor2);

    GLint baseColorLoc = glGetUniformLocation(shaderProgram.ID, "baseColor");

    glUniform3fv(baseColorLoc, 1, glm::value_ptr(changingColor));
    // Tell OpenGL which Shader Program we want to use
    shaderProgram.Activate();
    // Bind the VAO so OpenGL knows to use it
    VAO1.Bind();
    float time3 = glfwGetTime() * 45 ;
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - previousTime;
    previousTime = currentTime;
   
    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor1));
	//glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, -0.0f, 0.0f));
	
    //glm::mat4 transform2 = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor2));
 
    translationX += deltaTime * translationSpeed;
    std::cout<< deltaTime <<translationX << std::endl;
    if (translationX >= translationLimit || translationX <= -translationLimit -0.2) {
   
        translationSpeed = -translationSpeed;
    }

    
    if (reverseDirection)
        translationX = -translationX;

    glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), glm::vec3(translationX, 0.0f, 0.0f));

    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform));

  
    
    // Draw primitives, number of triangles, datatype of indices, index of indices
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)0);
    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(transform2));
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
    //renderCircle();
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
