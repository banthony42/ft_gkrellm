#ifndef RENDERER_HPP
# define RENDERER_HPP

# include <string>
# include "ProgramGlsl.hpp"
# include "TextRenderer.hpp"
# include "Window.hpp"
# include "AGraphical.hpp"
# include "Window.hpp"

class Renderer :public AGraphical
{
public:
	Renderer();
	Renderer(Renderer const &copy);
	~Renderer();
	void updateVisual();
	void refreshVisual();
	void generateCurveDisplay(float lastPoint, std::string label, AModule const &mod);
	void generateValDisplay(float val, std::string label, AModule const &mod);
	void generateStringDisplay(std::string str, std::string label, AModule const &mod);
	void close(void);
	bool isOpen(void);
	Renderer	&operator=(Renderer const &rhs);
protected:
private:
	class TextureData
	{
	public:
		TextureData();
		~TextureData();
		void updateGl();
		void addValue(const float val);
		void setText(const std::string text);
		const std::string &getText();
		GLuint getTexId(void);
		float getMin(void) const;
		float getMax(void) const;
		unsigned int getHeight(void) const;
		void setHeight(const unsigned int height);
		float operator[](unsigned int v) const;
	private:
		TextureData(TextureData const &copy);
		TextureData	&operator=(TextureData const &rhs);
		GLuint _tex_id;
		float _data[256];
		float _dataMin;
		float _dataMax;
		std::string _text;
		unsigned int _moduleHeight;
	};

	Window _win;
	ProgramGlsl _courbe;
	GLuint _vao;
	GLuint _vbo;
	TextRenderer _textRD;
	GLint _uni_min;
	GLint _uni_max;
	GLint _uni_tex;
	static const GLfloat _vertPlane[12];

	unsigned int _modCount;
	TextureData  _modData[10];
	unsigned int _moduleTotalHeight;
};

#endif
