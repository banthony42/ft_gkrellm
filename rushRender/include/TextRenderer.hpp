#ifndef TEXTRENDERER_HPP
# define TEXTRENDERER_HPP

# include <string>
# include "ProgramGlsl.hpp"
# include "Texture.hpp"

class TextRenderer
{
public:
	TextRenderer();
	TextRenderer(TextRenderer const &copy);
	~TextRenderer();
	TextRenderer	&operator=(TextRenderer const &rhs);
	void update_font_data(unsigned int w, unsigned int h);
	void render_text(const std::string str, const float x, const float y);
protected:
private:
	ProgramGlsl _prog;
	Texture _font;
	GLint _uni_tex_id;
	GLint _uni_font_id;
	GLuint _vba;
	GLuint _vbo;
	int _font_size;
	int _font_char_space;
	int _font_line_space;
	float _f_font_size_x;
	float _f_font_size_y;
	float _f_font_char_space;
	float _f_font_line_space;
};

#endif
