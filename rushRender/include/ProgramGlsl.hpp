#ifndef PROGRAMGLSL_HPP
# define PROGRAMGLSL_HPP

# include <string>
# include "Shader.hpp"

class ProgramGlsl
{
public:
	ProgramGlsl();
	ProgramGlsl(const Shader &frag);
	ProgramGlsl(const Shader &vertex, const Shader &frag);
	ProgramGlsl(const Shader &vertex, const Shader &frag, const Shader &geom);
	ProgramGlsl(ProgramGlsl const &copy);
	~ProgramGlsl();
	ProgramGlsl	&operator=(ProgramGlsl const &rhs);
	void bind();
	GLuint getProg();
protected:
private:

	GLuint _prog;
};

#endif


/*void			Shaders::uniformMat4(GLchar *name, GLfloat *mat)
{
	GLint id = glGetUniformLocation(_program, name);
	glUniformMatrix4fv(id, 1, GL_FALSE, mat);
}

void			Shaders::uniform1f(GLchar *name, GLfloat value)
{
	GLint id = glGetUniformLocation(_program, name);
	glUniform1f(id, value);
}

void			Shaders::uniform2f(GLchar *name, GLfloat *value)
{
	GLint id = glGetUniformLocation(_program, name);
	glUniform2fv(id, 1, value);
}

void			Shaders::uniform3f(GLchar *name, GLfloat *value)
{
	GLint id = glGetUniformLocation(_program, name);
	glUniform3fv(id, 1, value);
}

void			Shaders::uniform4f(GLchar *name, GLfloat *value)
{
	GLint id = glGetUniformLocation(_program, name);
	glUniform4fv(id, 1, value);
}

void			Shaders::uniform1i(GLchar *name, GLint value)
{
	GLint id = glGetUniformLocation(_program, name);
	glUniform1i(id, value);
}*/
