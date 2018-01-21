#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <string>
# include <iostream>
# include <stdexcept>
# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# ifndef TORADIANS
#  define TORADIANS(x)	(x * 0.0174533f)
# endif
# include "Except.hpp"
# include "TextRenderer.hpp"

class Window
{
public:
	Window(unsigned int width = 512, unsigned int height = 480);
	~Window();
	void				loop(void);
	void				update(void);
	void				render(void);
	void				close(void);
	bool				isOpen(void);
	GLFWwindow			*getGLFW(void);
	void				setSize(unsigned int width, unsigned int height);
	unsigned int getWidth();
	unsigned int getHeight();
protected:
private:
	Window(Window const &copy);
	Window	&operator=(Window const &rhs);

	GLFWwindow *_win;
	unsigned int _width;
	unsigned int _height;
};

#endif
