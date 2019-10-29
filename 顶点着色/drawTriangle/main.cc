#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
/*
�û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�������
���ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵��á�
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//��Դ������ַ���
const char * fragShaderSource = 
"#version 400 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0f);\n"
"	ourColor = aColor;\n"
"}\0";


const char * fragShaderSource1 =
"#version 400 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

GLFWwindow* window;// = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

float vertices3[] =
{
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // ����
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // ����
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // ����
};

int init()
{
	/*
	 *���ȣ�������main�����е���glfwInit��������ʼ��GLFW��
	 *Ȼ�����ǿ���ʹ��glfwWindowHint����������GLFW��
	 *glfwWindowHint�����ĵ�һ����������ѡ������ƣ�
	 *���ǿ��ԴӺܶ���GLFW_��ͷ��ö��ֵ��ѡ��
	 *�ڶ�����������һ�����Σ������������ѡ���ֵ��
	*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*
	 *glfwCreateWindow������Ҫ���ڵĿ�͸���Ϊ����ǰ����������
	 *������������ʾ������ڵ����ƣ����⣩����������ʹ��"LearnOpenGL"��
	*/
	//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//�������ĺ�Window������
	glfwMakeContextCurrent(window);
	//ע��ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*
	GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD��
	*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}



/*
�������Ǽ���û��Ƿ����˷��ؼ�(Esc)�����û�а��£�glfwGetKey���᷵��GLFW_RELEASE��
����û���ȷ�����˷��ؼ���
���ǽ�ͨ��glfwSetwindowShouldCloseʹ�ð�WindowShouldClose��������Ϊ true�ķ����ر�GLFW��
��һ��whileѭ����������⽫��ʧ�ܣ����򽫻�رա�
*/
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*
���֡�����С������Ҫһ��GLFWwindow��Ϊ���ĵ�һ���������Լ�����������ʾ���ڵ���ά�ȡ�
ÿ�����ڸı��С��GLFW�������������������Ӧ�Ĳ������㴦��
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//����OpenGL��Ⱦ���ڵĳߴ��С�����ӿ�(Viewport)
	//glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
	glViewport(0, 0, width, height);
}

int main()
{
	int ret = 0;

	ret = init();

	

	int success;
	char infoLog[512];

	//vbo������ݣ�VAO������VBO��
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	//��vao��OpenGL
	glBindVertexArray(VAO);

	//����VBO
	glGenBuffers(1, &VBO);
	//��VBO��OpenGL
	//�������Դ�ռ�
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//�����������鵽һ�����������У���OpenGLʹ��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//������ɫ������
	glShaderSource(vertexShader, 1,&fragShaderSource, NULL);//��Դ��
	glCompileShader(vertexShader);//������ɫ������
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << infoLog << std::endl;
	}

	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource1, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << infoLog << std::endl;
	}

	int	shaderProgramID = glCreateProgram();//������ɫ������
	glAttachShader(shaderProgramID, vertexShader);//������ɫ������
	glAttachShader(shaderProgramID, fragShader);
	glLinkProgram(shaderProgramID);//�������ɳ���
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::LINKING_FAILED\n" << infoLog << std::endl;
		std::cout << infoLog << std::endl;
	}
	/*glDeleteShader(fragID);
	glDeleteShader(fragShaderID);*/
	glUseProgram(shaderProgramID);

	
	

	/*
	 *���ǿ��԰�����֮Ϊ��Ⱦѭ��(Render Loop)��������������GLFW�˳�ǰһֱ��������
	*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(shaderProgramID);//ʹ���Զ������ɫ������
		glBindVertexArray(VAO);
		
		//����OpenGL	����������
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);//�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		glfwPollEvents();//���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
	}

	glfwTerminate();
	return 0;
}