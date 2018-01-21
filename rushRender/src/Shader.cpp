/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouthie <jrouthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:19:40 by jrouthie          #+#    #+#             */
/*   Updated: 2018/01/20 16:32:06 by jrouthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Shader.hpp"

Shader::Shader()
{

}

static char *getFileContent(std::string file)
{
	std::ifstream t;
	t.open(file);
	if (t.fail())
	{
		throw Except("file invalide");
	}
	t.seekg(0, std::ios::end);
	int l = t.tellg();
	t.seekg(0, std::ios::beg);
	char *buf = new char[l + 1];
	t.read(buf, l);
	buf[l] = '\0';
	t.close();
	return (buf);
}

static void get_shader_log(GLuint shader_id)
{
	GLint	result;
	int		info_log_length;

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	if (result == 0)
	{
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
		if (!info_log_length)
			throw Except("(Shader) Error");
		char *buf = new char[info_log_length];
		glGetShaderInfoLog(shader_id, info_log_length, NULL, buf);
		std::string str("(Shader) Error : \n");
		str += buf;
		delete[] buf;
		throw Except(str);
	}
}

Shader::Shader(std::string file, GLenum type) : _type(type)
{
	if (type == 0)
	{
		uint p = file.find_last_of('.');
		if (p)
		{
			if (file[p - 1] == 'v')
				type = GL_VERTEX_SHADER;
			else if (file[p - 1] == 'f')
				type = GL_FRAGMENT_SHADER;
			else if (file[p - 1] == 'g')
				type = GL_GEOMETRY_SHADER;
			else
				throw Except("(Shader) Unknow shader type");
		}
		else
			throw Except("(Shader) Unknow shader type");
	}
	file = "res/" + file;
	char *script = getFileContent(file.c_str());
	if (!script)
		throw Except();//"(Shader) Erreur lecture du fichier"
	_shader = glCreateShader(type);
	glShaderSource(_shader, 1, static_cast<const GLchar *const*>(&script), NULL);
	glCompileShader(_shader);
	delete script;
	get_shader_log(_shader);
}

Shader::~Shader()
{
	glDeleteShader(_shader);
}

GLuint Shader::getShader() const
{
	return (this->_shader);
}

GLenum Shader::getType() const
{
	return (_type);
}

Shader::Shader(Shader const &copy)
{
	*this = copy;
}

Shader	&Shader::operator=(Shader const &rhs)
{
	(void)rhs;
	return (*this);
}
