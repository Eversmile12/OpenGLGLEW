#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

GLuint uniformModel;
static const char* vShader = "												\n\
#version 330																\n\
layout (location = 0) in vec3 pos;											\n\
uniform mat4 model;															\n\
void main()																	\n\
{																			\n\
	gl_Position = model*vec4(pos.x, pos.y, pos.z, 1.0);					\n\
}";

static const char* fShader = "								\n\
#version 330												\n\
out vec4 color; 											\n\
void main()													\n\
{															\n\
	color = vec4(1.0, 0.0, 0.0, 1.0);						\n\
}";

void AddShader(GLuint program, const char* shaderSource, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	GLint codeLength[]{ (GLint)strlen(shaderSource) };
	glShaderSource(shader, 1, &shaderSource, codeLength);
	glCompileShader(shader);

	GLint result{ 0 };
	GLchar elog[512]{ 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, 512, NULL, elog);
		std::cout << "ERROR::COMPILING::SHADER\n" << elog;
		return;
	}

	glAttachShader(program, shader);

	
}

GLuint CompileShaders() {
	GLuint program = glCreateProgram();

	if (!program)
	{
		std::cout << "ERROR::CREATING::SHADER::PROGRAM \n";
		return 1;
	}
	AddShader(program, vShader, GL_VERTEX_SHADER);
	AddShader(program, fShader, GL_FRAGMENT_SHADER);

	GLint result{ 0 };
	GLchar elog[512]{ 0 };

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(program, 512, NULL, elog);
		std::cout << "ERROR::LINKING::PROGRAM\n" << elog;
		return 1;
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(program, 512, NULL, elog);
		std::cout << "ERROR::VALIDATING::PROGRAM\n" << elog;
		return 1;
	}

	uniformModel = glGetUniformLocation(program, "model");

	return program;
}

GLuint CreateTriangle(GLfloat vertices[])
{
	GLuint VAO{ 0 }, VBO{ 0 };
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*9, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_VERTEX_ARRAY, 0);

	return VAO;
}

int main() {

	if (!glfwInit())
	{
		std::cout << "ERROR::INITIALIZING::GLFW\n";
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif // __APPLE__

	const unsigned int WIDTH{ 800 }, HEIGHT{ 600 };
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Alternate OpenGl", 0, 0);
	
	if (!mainWindow) 
	{
		std::cout << "ERROR::CREATING::GLFW::WINDOW\n";
		glfwTerminate();
		return -1;
	}

	int bufferWidth, bufferHeight;

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(mainWindow);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::INITIALIZING::GLEW\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return -1;
	}
	
	glViewport(0, 0, bufferWidth, bufferHeight);
	GLfloat veticesOne[]{
			-0.5f, -0.5f, 0.0f,
			0.0f, -0.5f, 0.0f,
			-0.25f, 0.0f, 0.0f
	};
	GLuint firstTriangle = CreateTriangle(veticesOne);
	GLuint program = CompileShaders();

	GLfloat verticesTwo[]{
			0.5f, 0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
			0.25f, 0.0f, 0.0f
	};
	GLuint secondTriangle = CreateTriangle(verticesTwo);
	bool direction = true;
	float triOffset{ 0 };
	float maxOffset{ 0.5f };
	float offsetIncrement{ 0.0005f };
	


	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		if (direction) {
			triOffset += offsetIncrement;
		}
		else {
			triOffset -= offsetIncrement;
		}

		if (abs(triOffset) > maxOffset) {
			direction = !direction;
		}

		glUseProgram(program);
		glm::mat4 model( 1.0f );
		model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		
		glBindVertexArray(firstTriangle);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(secondTriangle);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(mainWindow);

	}


}