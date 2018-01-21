#include <iostream>
#include "Window.hpp"

static void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mods)
{
	Window	*win;

	(void)scancode;
	(void)mods;
	win = static_cast<Window *>(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
			win->close();
		else if (key == GLFW_KEY_SPACE)
		{
		}
	}
}

static void win_resize_callback(GLFWwindow *window, int width, int height)
{
	Window	*win;

	win = static_cast<Window *>(glfwGetWindowUserPointer(window));
	win->setSize(width, height);
	glViewport(0, 0, width, height);
}

Window::Window(unsigned int width, unsigned int height)
{
	if (!glfwInit())
	{
		std::exception();//"Erreur init glfw!"
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, false);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWmonitor *m = glfwGetPrimaryMonitor();
	const GLFWvidmode *vm = glfwGetVideoMode(m);
	height = vm->height - 22;
	if ((_win = glfwCreateWindow(width, height, "ft_gkrellm", NULL, NULL)))
	{
		glfwSetWindowPos(_win, vm->width - width, 22);
		glfwMakeContextCurrent(_win);
		glfwSetWindowUserPointer(_win, this);
		glfwSetKeyCallback(_win, key_callback);
		// glfwSetCursorPosCallback(_win, cursor_position_callback);
		// glfwSetMouseButtonCallback(_win, mouse_button_callback);
		glfwSetFramebufferSizeCallback(_win, win_resize_callback);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			glfwDestroyWindow(_win);
			glfwTerminate();
			std::exception();//"Erreur init glew!"
		}
		win_resize_callback(_win, width, height);
	}
	else
	{
		glfwTerminate();
		std::exception();//"La fenetre n'a pas pu etre creer."
	}
	glEnable(GL_BLEND);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSwapInterval(1);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
}

Window::~Window()
{
	if (_win)
		glfwDestroyWindow(_win);
	glfwTerminate();
}

Window::Window(Window const &copy)
{
	*this = copy;
}

Window	&Window::operator=(Window const &rhs)
{
	(void)rhs;
	return (*this);
}

void Window::loop(void)
{
	while (isOpen())
	{
		update();
		render();
	}
}

void Window::update(void)
{
	glfwPollEvents();
}

void Window::render(void)
{
	// glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// glViewport(0, 0, _width, _height);
	glfwSwapBuffers(_win);
	glClearColor(0.6, 0.6, 0.6, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::close(void)
{
	glfwSetWindowShouldClose(_win, GLFW_TRUE);
}

bool Window::isOpen(void)
{
	return (!glfwWindowShouldClose(_win));
}

GLFWwindow *Window::getGLFW(void)
{
	return (_win);
}

void Window::setSize(unsigned int width, unsigned int height)
{
	_width = width;
	_height = height;
}

unsigned int Window::getWidth()
{
	return (_width);
}
unsigned int Window::getHeight()
{
	return (_height);
}
