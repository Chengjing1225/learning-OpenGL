#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "myShader.h"
//#include "FileSystem.h"


using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float screenWidth;
float screenHeight;

//float mixValue = 0.2f;


//#pragma warning(disable : 4996)
#pragma warning(suppress : 4996)
int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	myShader ourShader("shader.vs", "shader.fs"); // you can name your shader files however you like

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions         // colors             //纹理
		//前
		 0.5f, 0.5f, 0.5f,   1.0f, 1.0f,			//右上
		 0.5f, -0.5f, 0.5f,  1.0f, 0.0f,			//右下
		 -0.5f, 0.5f, 0.5f,  0.0f, 1.0f,			//左上 
		 0.5f, -0.5f, 0.5f,  1.0f, 0.0f,			//右下
		 -0.5f,-0.5f, 0.5f,  0.0f, 0.0f,		    //左下
		 -0.5f, 0.5f, 0.5f,  0.0f, 1.0f,			//左上 
		 //上
		 0.5f, 0.5f, -0.5f,   1.0f, 1.0f,			//右上
		 0.5f, 0.5f, 0.5f,  1.0f, 0.0f,				//右下
		 -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,			//左上 
		 0.5f, 0.5f, 0.5f,  1.0f, 0.0f,				//右下
		 -0.5f,0.5f, 0.5f,  0.0f, 0.0f,				//左下
		 -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,			//左上 
		 //右
		 0.5f, 0.5f, -0.5f,   1.0f, 1.0f,			//右上
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,			//右下
		 0.5f, 0.5f, 0.5f,  0.0f, 1.0f,			//左上 
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,			//右下
		 0.5f,-0.5f, 0.5f,  0.0f, 0.0f,				//左下
		 0.5f, 0.5f, 0.5f,  0.0f, 1.0f,				//左上 
		  
		 //左
		 -0.5f, 0.5f, 0.5f,   1.0f, 1.0f,			//右上
		 -0.5f, -0.5f, 0.5f,  1.0f, 0.0f,			//右下
		 -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,			//左上 
		 -0.5f, -0.5f, 0.5f,  1.0f, 0.0f,			//右下
		 -0.5f,-0.5f, -0.5f,  0.0f, 0.0f,			//左下
		 -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,			//左上 
		 //后
		 -0.5f, 0.5f, -0.5f,   1.0f, 1.0f,			//右上
		 -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,			//右下
		 0.5f, 0.5f, -0.5f,  0.0f, 1.0f,			//左上 
		 -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,			//右下
		 0.5f,-0.5f, -0.5f,  0.0f, 0.0f,		    //左下
		 0.5f, 0.5f, -0.5f,  0.0f, 1.0f,			//左上 
		 //底
		 -0.5f, -0.5f, 0.5f,   1.0f, 1.0f,			//右上
		 -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,			//右下
		 0.5f, -0.5f, 0.5f,  0.0f, 1.0f,			//左上 
		 -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,			//右下
		 0.5f,-0.5f, -0.5f,  0.0f, 0.0f,			//左下
		 0.5f, -0.5f,0.5f,  0.0f, 1.0f,			    //左上 

	};
	glm::vec3 cubePositions[] = {
			 glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)

	};
	/*unsigned int  indices[] = {
		0,1,3,
		1,2,3
	};*/

	unsigned int VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//第一个纹理
	unsigned int texture1;
	unsigned int texture2;
	glGenTextures(1, &texture1);	
	glBindTexture(GL_TEXTURE_2D, texture1);	
	//为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);//翻转y轴
	
	unsigned char *data = stbi_load(".\\image\\container.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //生成纹理
		glGenerateMipmap(GL_TEXTURE_2D);	//自动生成多级渐远纹理
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);	//释放图像内存



	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load(".\\image\\awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to Load Texture" << endl;
	}
	stbi_image_free(data);

	ourShader.use();//设置uniform之前激活纹理
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		glActiveTexture(GL_TEXTURE0);//激活纹理单元
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.use();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		
		
		//变换矩阵传递给着色器
		
		/*unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);*/
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);
			ourShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	   /* transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = sin(glfwGetTime());
		transform = glm::scale(transform,  glm::vec3(scaleAmount,scaleAmount,scaleAmount));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
				
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return  0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


