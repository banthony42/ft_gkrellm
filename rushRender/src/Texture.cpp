#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Texture.hpp"
#include "Except.hpp"

Texture::Texture()
{

}

Texture::Texture(std::string file, const GLint internalFormat)
{
	file = "res/" + file;
	uint p = file.find_last_of('.');
	if (p)
	{
		std::string ext = file.substr(p + 1);
		if (ext == "bmp")
			loadFromBmp(file, internalFormat);
		else
			throw Except("(Texture) Unknow img ext");
	}
	else
		throw Except("(Texture) Unknow file");

	glGenTextures(1, &_tex_id);
	updateGl();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{

}

Texture::Texture(Texture const &copy)
{
	*this = copy;
}

Texture	&Texture::operator=(Texture const &rhs)
{
	(void)rhs;
	return (*this);
}

void Texture::updateGl()
{
	glBindTexture(_target, _tex_id);
	glTexImage2D(_target,
		_level,
		_internalformat,
		_width,
		_height,
		_border,
		_format,
		_type,
		_data);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _tex_id);
}

void Texture::loadFromBmp(const std::string file, const GLint internalFormat)
{
	std::ifstream t;
	t.open(file);
	if (t.fail())
	{
		throw Except("bmp file invalide");
	}
	Texture::bmp_header header;
	Texture::bmp_infoheader info;
	t.read(reinterpret_cast<char*>(&header), 14);
	if (!t || header.type != 19778)
		throw Except("bmp header invalide");
	t.read(reinterpret_cast<char*>(&info), 40);
	if (!t)
		throw Except("bmp info invalide");
	_width = info.width;
	_height = info.height;
	if (!info.imagesize)
		info.imagesize = info.width * info.height * (info.bits / 8);
	_data = new char[info.imagesize];
	t.read(static_cast<char*>(_data), info.imagesize);
	if (!t || header.type != 19778)
		throw Except("bmp read invalide");
	t.close();
	_target = GL_TEXTURE_2D;
	_level = 0;
	_internalformat = internalFormat;
	_border = 0;
	_format = (info.bits == 24 ? GL_BGR : GL_BGRA);
	_type = GL_UNSIGNED_BYTE;
}
