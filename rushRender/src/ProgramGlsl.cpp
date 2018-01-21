#include <iostream>
#include "ProgramGlsl.hpp"

static void get_program_log(GLuint shader_id)
{
	GLint	result;
	int		info_log_length;

	glGetProgramiv(shader_id, GL_LINK_STATUS, &result);
	if (result == 0)
	{
		glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
		if (!info_log_length)
			throw Except("(Program) Error");
		char *buf = new char[info_log_length];
		glGetProgramInfoLog(shader_id, info_log_length, NULL, buf);
		std::string str("(Program) Error : \n");
		str += buf;
		delete[] buf;
		throw Except(str);
	}
}

ProgramGlsl::ProgramGlsl(const Shader &frag)
{
	_prog = glCreateProgram();
	if (!_prog)
		throw Except("(Program) Error glCreateProgram");
	glAttachShader(_prog, frag.getShader());
	glLinkProgram(_prog);
	get_program_log(_prog);
	glDetachShader(_prog, frag.getShader());
}

ProgramGlsl::ProgramGlsl(const Shader &vertex, const Shader &frag)
{
	_prog = glCreateProgram();
	if (!_prog)
		throw Except("(Program) Error glCreateProgram");
	glAttachShader(_prog, vertex.getShader());
	if (glGetError() != GL_NO_ERROR) throw std::exception();
	glAttachShader(_prog, frag.getShader());
	glLinkProgram(_prog);
	get_program_log(_prog);
	glDetachShader(_prog, vertex.getShader());
	glDetachShader(_prog, frag.getShader());
}

ProgramGlsl::ProgramGlsl(const Shader &vertex, const Shader &frag,
	const Shader &geom)
{
	_prog = glCreateProgram();
	if (!_prog)
		throw Except("(Program) Error glCreateProgram");
	glAttachShader(_prog, vertex.getShader());
	glAttachShader(_prog, frag.getShader());
	glAttachShader(_prog, geom.getShader());
	glLinkProgram(_prog);
	get_program_log(_prog);
	glDetachShader(_prog, vertex.getShader());
	glDetachShader(_prog, frag.getShader());
	glDetachShader(_prog, geom.getShader());
}

ProgramGlsl::ProgramGlsl()
{
}

ProgramGlsl::~ProgramGlsl()
{
	glDeleteProgram(_prog);
}

void ProgramGlsl::bind()
{
	glUseProgram(_prog);
}

GLuint ProgramGlsl::getProg()
{
	return (_prog);
}

ProgramGlsl::ProgramGlsl(ProgramGlsl const &copy)
{
	*this = copy;
}

ProgramGlsl	&ProgramGlsl::operator=(ProgramGlsl const &rhs)
{
	(void)rhs;
	return (*this);
}
