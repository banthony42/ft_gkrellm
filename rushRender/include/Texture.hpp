#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include <string>
# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>

class Texture
{
public:
	Texture();
	Texture(std::string file, const GLint internalFormat = GL_RGB);
	Texture(Texture const &copy);
	~Texture();
	Texture	&operator=(Texture const &rhs);
	void updateGl();
	void bind();
protected:
private:
	void loadFromBmp(const std::string file, const GLint internalFormat);

	GLuint _tex_id;
	GLenum _target;
	GLint _level;
	GLint _internalformat;
	GLsizei _width;
	GLsizei _height;
	GLint _border;
	GLenum _format;
	GLenum _type;
	void *_data;

	# pragma pack(push, 1)
	struct			bmp_header
	{
		unsigned short int	type;
		unsigned int		size;
		unsigned short int	reserved1;
		unsigned short int	reserved2;
		unsigned int		offset;
	};
	struct			bmp_infoheader
	{
		unsigned int		size;
		unsigned int		width;
		unsigned int		height;
		unsigned short int	planes;
		unsigned short int	bits;
		unsigned int		compression;
		unsigned int		imagesize;
		unsigned int		xresolution;
		unsigned int		yresolution;
		unsigned int		ncolours;
		unsigned int		importantcolours;
	};
	# pragma pack(pop)
};

#endif
