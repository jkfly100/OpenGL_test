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
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";


const char * fragShaderSource1 =
"#version 400 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

GLFWwindow* window;// = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

float vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

float vertices1[] =
{
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	
};

float vertices2[] =
{
	-0.5f, 0.5f, 0.0f,
	0.0f, -0.5f, 0.0f,
	-1.0f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	1.0f, -0.5f, 0.0f,
};

unsigned int indices[] =
{
	0, 1, 3,
	1, 2, 3
};

unsigned int indices1[] =
{
	0, 1, 2,
	3, 1, 4
};

void setFragColor(int &shaderProgramID)
{
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorlocation = glGetUniformLocation(shaderProgramID, "fragShaderSource1");
	glUseProgram(shaderProgramID);
	glUniform4f(vertexColorlocation, 0.0f, greenValue, 0.0f, 1.0f);
}

void VAOset()
{
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3 * sizeof(float)ָ��������xyz����ֵռ�õĿռ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	
}

void VAOset2()
{
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
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//�����������鵽һ�����������У���OpenGLʹ��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	// 3 * sizeof(float)ָ��������xyz����ֵռ�õĿռ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


}



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

	VAOset2();

	int success;
	char infoLog[512];

	int fragID = glCreateShader(GL_VERTEX_SHADER);//������ɫ������
	glShaderSource(fragID, 1,&fragShaderSource, NULL);//��Դ��
	glCompileShader(fragID);//������ɫ������

	glGetProgramiv(fragID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << infoLog << std::endl;
	}

	int fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderID, 1, &fragShaderSource1, NULL);
	glCompileShader(fragShaderID);

	glGetProgramiv(fragShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << infoLog << std::endl;
	}

	int	shaderProgramID = glCreateProgram();//������ɫ������
	glAttachShader(shaderProgramID, fragID);//������ɫ������
	glAttachShader(shaderProgramID, fragShaderID);
	glLinkProgram(shaderProgramID);//�������ɳ���

	//glDeleteShader(fragID);
	//glDeleteShader(fragShaderID);
	

	/*
	 *���ǿ��԰�����֮Ϊ��Ⱦѭ��(Render Loop)��������������GLFW�˳�ǰһֱ��������
	*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgramID);//ʹ���Զ������ɫ������
		

		//������ɫ��
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorlocation = glGetUniformLocation(shaderProgramID, "ourColor");
		//glUseProgram(shaderProgramID);
		glUniform4f(vertexColorlocation, 0.0f, greenValue, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		//����OpenGL	����������
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);//�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		glfwPollEvents();//���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
	}

	glfwTerminate();
	return 0;
}