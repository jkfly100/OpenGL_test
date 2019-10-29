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
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

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

void VAOTwoTriangle()
{
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

void rectangle()
{

	VAOset();
}

void twoTriangle()
{
	VAOTwoTriangle();
}


int main()
{
	int ret = 0;

	ret = init();

	rectangle();

	int fragID = glCreateShader(GL_FRAGMENT_SHADER);//������ɫ������
	glShaderSource(fragID, 1,&fragShaderSource, NULL);//��Դ��
	glCompileShader(fragID);//������ɫ������

	int	shaderProgramID = glCreateProgram();//������ɫ������
	glAttachShader(shaderProgramID, fragID);//������ɫ������
	glLinkProgram(shaderProgramID);//�������ɳ���

	/*
	 *���ǿ��԰�����֮Ϊ��Ⱦѭ��(Render Loop)��������������GLFW�˳�ǰһֱ��������
	*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgramID);//ʹ���Զ������ɫ������
		//����OpenGL	����������
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);//�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		glfwPollEvents();//���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
	}

	glfwTerminate();
	return 0;
}