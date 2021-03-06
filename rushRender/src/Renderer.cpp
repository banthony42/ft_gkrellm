#include <iostream>
#include <sstream>
#include <cmath>
#include "Renderer.hpp"



const GLfloat Renderer::_vertPlane[12] =
{
	-1.0f, -1.0f,
	1.0f, -1.0f,
	-1.0f,  1.0f,
	1.0f, 1.0f,
	-1.0f,  1.0f,
	1.0f, -1.0f,
};

Renderer::Renderer() :
	_win(),
	_courbe(Shader("graph_v.glsl"), Shader("graph_f.glsl")),
	_textRD(),
	_uni_min(glGetUniformLocation(_courbe.getProg(), "dataMin")),
	_uni_max(glGetUniformLocation(_courbe.getProg(), "dataMax")),
	_uni_tex(glGetUniformLocation(_courbe.getProg(), "tex")),
	_moduleTotalHeight(0)
{
	_textRD.update_font_data(_win.getWidth(), _win.getHeight());

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertPlane),
		_vertPlane, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	for (std::list<AModule*>::const_iterator iterator = get_moduleList().begin();
		iterator != get_moduleList().end(); ++iterator)
	{
		AModule* mod = *iterator;
		if (!mod->getIsActive())
			break;
		// _modCount++;
		// _modData.push_back(new TextureData());
		// int pos = mod->getPosition() - 1;

		// _modData[pos]->setText(mod->getName());
		// _modData[pos]->setHeight(mod->getLen());
	}
	// _modCount = 10;
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	while (_modData.size())
	{
		delete _modData[_modData.size() - 1];
		_modData.pop_back();
	}
}

void Renderer::updateVisual()
{
	_win.update();
	for (std::list<AModule*>::const_iterator iterator = get_moduleList().begin();
		iterator != get_moduleList().end(); ++iterator)
	{
		AModule* mod = *iterator;
		if (!mod->getIsActive())
			break;
		mod->updateSysInfo();
		generateModuleDisplay(*mod);
	}
}

void Renderer::refreshVisual()
{
	unsigned int modCount = _modData.size();
	float tth = 0;
	if (modCount)
	{
		for (size_t i = 0; i < modCount; i++)
		{
			float hf = static_cast<float>(_win.getHeight()) *
				static_cast<float>(_modData[i]->getHeight()) /
				static_cast<float>(_moduleTotalHeight);
			unsigned int h = static_cast<unsigned int>(hf);
			// unsigned int h = _win.getHeight() / _modData.size();
			// std::cout << "h : " << _modData[i]->getHeight() << " : " << h << std::endl;
			_textRD.update_font_data(_win.getWidth(), h);
			glViewport(0, _win.getHeight() - h - tth, _win.getWidth(), h);
			_courbe.bind();
			glBindVertexArray(_vao);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_1D, _modData[i]->getTexId());
			glUniform1f(_uni_min, _modData[i]->getMin());
			glUniform1f(_uni_max, _modData[i]->getMax());
			glUniform1i(_uni_tex, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
			_textRD.render_text(_modData[i]->getText(), -1, -1);
			tth += hf;
		}
	}
	_win.render();
}

void Renderer::generateCurveDisplay(float lastPoint, std::string label, AModule const &mod)
{
	// std::cout << "generateCurveDisplay : " << lastPoint << std::endl;
	std::string cd = mod.getName() + '.' + label;
	for (size_t i = 0; i < _modData.size(); i++)
	{
		if (_modData[i]->getName() == cd)
		{
			std::ostringstream str;
			str << label << " : " << lastPoint;
			_modData[i]->setText(str.str());
			_modData[i]->addValue(lastPoint);
			return;
		}
	}
	TextureData *data = new TextureData();
	data->setName(cd);
	data->setHeight(50);
	_moduleTotalHeight += 50;
	_modData.push_back(data);
}

void Renderer::generateValDisplay(float val, std::string label, AModule const &mod)
{
	// std::cout << "generateValDisplay : (" << label << ")" << val << std::endl;
	std::string cd = mod.getName() + '.' + label;
	for (size_t i = 0; i < _modData.size(); i++)
	{
		if (_modData[i]->getName() == cd)
		{
			std::ostringstream str;
			str << label << " : " << val;
			_modData[i]->setText(str.str());
			return;
		}
	}
	TextureData *data = new TextureData();
	data->setName(cd);
	data->setHeight(10);
	_moduleTotalHeight += 10;
	_modData.push_back(data);

	// int pos = mod.getPosition() - 1;
	// _modData[pos]->addValue(val);
}

void Renderer::generateStringDisplay(std::string val, std::string label, AModule const &mod)
{
	// std::cout << "generateStringDisplay : " << str << std::endl;
	std::string cd = mod.getName() + '.' + label;
	for (size_t i = 0; i < _modData.size(); i++)
	{
		if (_modData[i]->getName() == cd)
		{
			std::ostringstream str;
			str << label << " : " << val;
			_modData[i]->setText(str.str());
			return;
		}
	}
	TextureData *data = new TextureData();
	data->setName(cd);
	data->setHeight(10);
	_moduleTotalHeight += 10;
	_modData.push_back(data);
}

void Renderer::close(void)
{
	_win.close();
}

bool Renderer::isOpen(void)
{
	return (_win.isOpen());
}

Renderer::Renderer(Renderer const &copy)
{
	*this = copy;
}

Renderer	&Renderer::operator=(Renderer const &rhs)
{
	(void)rhs;
	return (*this);
}


/*
**	TextureData
**
*/

Renderer::TextureData::TextureData() :
	_dataMin(0), _dataMax(0)
{
	glGenTextures(1, &_tex_id);
	for (int i = 0; i < 256; i++)
	{
		_data[i] = 0;
	}
	updateGl();
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Renderer::TextureData::updateGl()
{
	glBindTexture(GL_TEXTURE_1D, _tex_id);
	glTexImage1D(GL_TEXTURE_1D,
		0,
		GL_RED,
		256,
		0,
		GL_RED,
		GL_FLOAT,
		_data);
}

void Renderer::TextureData::addValue(const float val)
{
	_dataMin = _data[0];
	_dataMax = _data[0];
	for (int i = 1; i < 256; i++)
	{
		if (_data[i] > _dataMax)
			_dataMax = _data[i];
		else if (_data[i] < _dataMin)
			_dataMin = _data[i];
		_data[i - 1] = _data[i];
	}
	_data[256 - 1] = val;
	updateGl();
}

void Renderer::TextureData::setText(const std::string text)
{
	_text = text;
}

const std::string &Renderer::TextureData::getText()
{
	return (_text);
}

GLuint Renderer::TextureData::getTexId(void)
{
	return (_tex_id);
}
float Renderer::TextureData::getMin(void) const
{
	return (_dataMin);
}

unsigned int Renderer::TextureData::getHeight(void) const
{
	return (_moduleHeight);
}

void Renderer::TextureData::setHeight(const unsigned int height)
{
	_moduleHeight = height;
}

float Renderer::TextureData::getMax(void) const
{
	return (_dataMax);
}
std::string Renderer::TextureData::getName(void) const
{
	return (_name);
}
void Renderer::TextureData::setName(const std::string name)
{
	_name = name;
}

float Renderer::TextureData::operator[](unsigned int v) const
{
	if (v >= 256)
		return (0);
	return (_data[v]);
}

Renderer::TextureData::~TextureData()
{
	glDeleteTextures(1, &_tex_id);
}

Renderer::TextureData::TextureData(Renderer::TextureData const &copy)
{
	*this = copy;
}

Renderer::TextureData &Renderer::TextureData::operator=(Renderer::TextureData const &rhs)
{
	(void)rhs;
	return (*this);
}
