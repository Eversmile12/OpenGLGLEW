//#include <stdio.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <string.h>
//#include <cmath>
//#include <GLM/mat4x4.hpp>
//
//
//GLuint VAO, VBO, EBO, program, xMoveUniform;
//static const char* vShader = "												\n\
//#version 330																\n\
//layout (location = 0) in vec3 pos;											\n\													\n\
//void main()																	\n\
//{																			\n\
//	gl_Position = vec4(0.4f*pos.x + xMove, 0.4f*pos.y, pos.z, 1.0);			\n\
//}";
//static const char* fShader = "								\n\
//#version 330												\n\
//out vec4 color; 											\n\
//void main()													\n\
//{															\n\
//	color = vec4(1.0, 0.0, 0.0, 1.0);						\n\
//}";
//
//
//
//
//void CreateRectangle() {
//	GLfloat vertices[]{
//		0.5f, 0.5f, 0.0f,
//		0.5, -0.5f, 0.0f,
//		-0.5f, -0.5f, 0.0f,
//		-0.5f, 0.5f, 0.0
//	};
//
//	unsigned int indices[]{
//		0, 1, 3,
//		1, 2, 3
//	};
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//}
//
//void CreateTriangle() {
//	GLfloat vertices[] = {
//		-1.0f, -0.5f, 0.0f,
//		0.0f, -0.5f, 0.0f,
//		-0.5f, 0.0f, 0.0f,
//		0.0f, -0.5f, 0.0f,
//		1.0f, -0.5f, 0.0f,
//		0.5f, 0.0f, 0.0f
//	};
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}
//
//void AddShader(GLuint program, const char* shaderSrc, GLenum shaderType)
//{
//	GLuint shader = glCreateShader(shaderType);
//	GLint codeLength[]{ (GLint)strlen(shaderSrc) };
//	glShaderSource(shader, 1, &shaderSrc, codeLength);
//	glCompileShader(shader);
//
//	GLint result = 0;
//	GLchar elog[512]{ 0 };
//
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
//	if (!result)
//	{
//		glGetShaderInfoLog(shader, 512, NULL, elog);
//		fprintf(stderr, "Error compiling the %d shader: %s \n", shaderType, elog);
//		return;
//	}
//
//	glAttachShader(program, shader);
//}
//
//void CompileShaders() {
//	program = glCreateProgram();
//
//	if (!program) {
//		printf("Failed to create program");
//		return;
//	}
//
//	AddShader(program, vShader, GL_VERTEX_SHADER);
//	AddShader(program, fShader, GL_FRAGMENT_SHADER);
//
//	
//
//	GLint result = 0;
//	GLchar elog[512]{ 0 };
//
//	glLinkProgram(program);
//	glGetProgramiv(program, GL_LINK_STATUS, &result);
//	if (!result)
//	{
//		glGetProgramInfoLog(program, 512, NULL, elog);
//		printf("ERR::LINKING::PROGRAM: '%s'\n", elog);
//		return;
//	}
//
//	glValidateProgram(program);
//	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
//	if (!result)
//	{
//		glGetProgramInfoLog(program, 512, NULL, elog);
//		printf("ERR::VALIDATING::PROGRAM: '%s'\n", elog);
//		return;
//	}
//
//	xMoveUniform = glGetUniformLocation(program, "xMove");
//
//}
//
//int main() {
//
//
//	if (!glfwInit())
//	{
//		printf("GLFW initialization failed");
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__:
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//	const GLuint WIDTH{ 800 }, HEIGHT{ 600 };
//	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", NULL, NULL);
//
//	if (!mainWindow)
//	{
//		printf("error creating GLFW Window");
//		glfwTerminate();
//		return -1;
//	}
//
//	int bufferWidth, bufferHeight;
//
//	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
//	glfwMakeContextCurrent(mainWindow);
//	glewExperimental = GL_TRUE;
//
//	if (glewInit() != GLEW_OK)
//	{
//		printf("GLEW init failed");
//		glfwDestroyWindow(mainWindow);
//		glfwTerminate();
//		return -1;
//	}
//
//	glViewport(0, 0, bufferWidth, bufferHeight);
//	CreateTriangle();
//	CompileShaders();
//
//	bool direction = true;
//	float triOffset = 0.0f;
//	float maxTriOffset = 0.7f;
//	float offsetIncrement = 0.0005f;
//
//	while(!glfwWindowShouldClose(mainWindow))
//	{
//		glfwPollEvents();
//
//	
//
//		if (direction) {
//			triOffset += offsetIncrement;
//		}
//		else {
//			triOffset -= offsetIncrement;
//		}
//
//		if (abs(triOffset) >= maxTriOffset) {
//			direction = !direction;
//		}
//
//		
//
//		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glUseProgram(program);
//		
//		glUniform1f(xMoveUniform, triOffset);
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//
//		glBindVertexArray(0);
//		glUseProgram(0);
//	
//		
//
//		glfwSwapBuffers(mainWindow);
//	}
//
//	return 0;
//}