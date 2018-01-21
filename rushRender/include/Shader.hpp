#ifndef SHADER_HPP
# define SHADER_HPP

# include <string>
# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "Except.hpp"
class Shader
{
public:
	/*
	** GL_VERTEX_SHADER
	** GL_FRAGMENT_SHADER
	** GL_GEOMETRY_SHADER
	*/
	Shader(const std::string file, const GLenum type = 0);
	~Shader();
	GLuint getShader() const;
	GLenum getType() const;
protected:
private:
	Shader();
	Shader(Shader const &copy);
	Shader	&operator=(Shader const &rhs);

	GLuint _shader;
	GLenum _type;
};

#endif
