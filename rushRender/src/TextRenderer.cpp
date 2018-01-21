#include <iostream>
#include "TextRenderer.hpp"

TextRenderer::TextRenderer() :
	_prog(Shader("font_v.glsl"), Shader("font_f.glsl"),
		Shader("font_g.glsl")), _font("font.bmp"),
		_uni_tex_id(glGetUniformLocation(_prog.getProg(), "tex")),
		_uni_font_id(glGetUniformLocation(_prog.getProg(), "font")),
		_font_size(32), _font_char_space(-15), _font_line_space(-4)
{
	glGenVertexArrays(1, &_vba);
	glGenBuffers(1, &_vbo);
	if (_uni_tex_id < 0 || _uni_font_id < 0 || !_vba || !_vbo)
		throw Except("TextRenderer error init");
}

void TextRenderer::update_font_data(unsigned int w, unsigned int h)
{
	_f_font_size_y = static_cast<float>(_font_size) / static_cast<float>(h);
	_f_font_size_x = static_cast<float>(_font_size) / static_cast<float>(w);
	_f_font_char_space = _f_font_size_x + static_cast<float>(_font_char_space) / static_cast<float>(w);
	_f_font_line_space = _f_font_size_y + static_cast<float>(_font_line_space) / static_cast<float>(h);
}

static inline unsigned char	get_font_char(char c)
{
	if (c >= ' ' && c <= '~')
		return ((unsigned char)c - ' ');
	return (0);
}

void TextRenderer::render_text(const std::string str, const float x, const float y)
{
	_prog.bind();
	glActiveTexture(GL_TEXTURE0);
	_font.bind();
	glUniform1i(_uni_tex_id, 0);
	glUniform2f(_uni_font_id, _f_font_size_x, _f_font_size_y);
	float	arr[3 * str.length()];
	float	p[2];

	p[0] = x;
	p[1] = y;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		arr[i * 3] = p[0];
		arr[i * 3 + 1] = -p[1];
		arr[i * 3 + 2] = get_font_char(str[i]);
		if (str[i] == '\n')
		{
			p[1] += _f_font_line_space;
			p[0] = x;
		}
		else if (str[i] == '\t')
			p[0] += _f_font_char_space * 4;
		else
			p[0] += _f_font_char_space;
	}
	glBindVertexArray(_vba);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(GLfloat) * 3 * str.length()), arr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_POINTS, 0, str.length());
	glBindVertexArray(0);
}

TextRenderer::~TextRenderer()
{

}

TextRenderer::TextRenderer(TextRenderer const &copy)
{
	*this = copy;
}

TextRenderer	&TextRenderer::operator=(TextRenderer const &rhs)
{
	(void)rhs;
	return (*this);
}
