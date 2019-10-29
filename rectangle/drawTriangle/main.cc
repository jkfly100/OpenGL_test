#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
/*
用户改变窗口的大小的时候，视口也应该被调整。
我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//将源码存入字符串
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
	//vbo存放数据，VAO来管理VBO；
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	//将vao绑定OpenGL
	glBindVertexArray(VAO);
	
	//生成VBO
	glGenBuffers(1, &VBO);
	//将VBO绑定OpenGL
	//即开辟显存空间
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//复制索引数组到一个索引缓冲中，供OpenGL使用
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	// 3 * sizeof(float)指步长，即xyz三个值占用的空间
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
	 *首先，我们在main函数中调用glfwInit函数来初始化GLFW，
	 *然后我们可以使用glfwWindowHint函数来配置GLFW。
	 *glfwWindowHint函数的第一个参数代表选项的名称，
	 *我们可以从很多以GLFW_开头的枚举值中选择；
	 *第二个参数接受一个整形，用来设置这个选项的值。
	*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*
	 *glfwCreateWindow函数需要窗口的宽和高作为它的前两个参数。
	 *第三个参数表示这个窗口的名称（标题），这里我们使用"LearnOpenGL"，
	*/
	//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//把上下文和Window绑定起来
	glfwMakeContextCurrent(window);
	//注册回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*
	GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
	*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}



/*
这里我们检查用户是否按下了返回键(Esc)（如果没有按下，glfwGetKey将会返回GLFW_RELEASE。
如果用户的确按下了返回键，
我们将通过glfwSetwindowShouldClose使用把WindowShouldClose属性设置为 true的方法关闭GLFW。
下一次while循环的条件检测将会失败，程序将会关闭。
*/
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*
这个帧缓冲大小函数需要一个GLFWwindow作为它的第一个参数，以及两个整数表示窗口的新维度。
每当窗口改变大小，GLFW会调用这个函数并填充相应的参数供你处理。
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)
	//glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
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

	int fragID = glCreateShader(GL_FRAGMENT_SHADER);//创建着色器对象
	glShaderSource(fragID, 1,&fragShaderSource, NULL);//绑定源码
	glCompileShader(fragID);//编译着色器对象

	int	shaderProgramID = glCreateProgram();//创建着色器程序
	glAttachShader(shaderProgramID, fragID);//附加着色器对象
	glLinkProgram(shaderProgramID);//连接生成程序

	/*
	 *我们可以把它称之为渲染循环(Render Loop)，它能在我们让GLFW退出前一直保持运行
	*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgramID);//使用自定义的着色器程序
		//告诉OpenGL	画的是三角
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);//函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
		glfwPollEvents();//函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
	}

	glfwTerminate();
	return 0;
}