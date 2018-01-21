#ifndef EXCEPT_HPP
# define EXCEPT_HPP

# include <string>
# include <stdexcept>

class Except : public std::exception
{
public:
	Except(const std::string txt = "") :
		_txt(txt) {std::exception();};
	virtual const char *what() const throw() {return (_txt.c_str());};
	virtual ~Except() throw() {};
protected:
private:
	std::string _txt;
};

#endif
