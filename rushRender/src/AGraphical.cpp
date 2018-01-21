/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AGraphical.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 11:26:26 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 21:28:40 by jrouthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AGraphical.hpp"
#include "AutoCast.template.hpp"
#include "UserModule.hpp"
#include "OsModule.hpp"
#include "ClockModule.hpp"
#include "NetworkModule.hpp"
#include "CpuModule.hpp"
#include "RamModule.hpp"
#include "get_config.hpp"


AGraphical::AGraphical(void) : IMonitorDisplay(),
	_isActive(false),
	_x(0),
	_y(0),
	_name("Unnamed AGraphical")
{
	this->_moduleList.push_back(new UserModule(false, 0, "USER", 0, 0));
	this->_moduleList.push_back(new OsModule(false, 0, "OS", 0, 0));
	this->_moduleList.push_back(new ClockModule(false, 0, "CLOCK", 0, 0));
	this->_moduleList.push_back(new CpuModule(false, 0, "CPU", 0, 0));
	this->_moduleList.push_back(new RamModule(false, 0, "RAM", 0, 0));
	this->_moduleList.push_back(new NetworkModule(false, 0, "NET", 0, 0));

	std::vector<std::string> const *config = get_config();
	if ((this->_nbActiveModule = init_list(*config, &(this->_moduleList))) == 0) {
		throw AGraphical::NoModuleException();
	}
	return ;
}

AGraphical::AGraphical(AGraphical const &src) : IMonitorDisplay(),
	_isActive(src.getIsActive()),
	_x(src.getX()),
	_y(src.getY()),
	_name(src.getName())
{
	return ;
}

AGraphical::~AGraphical(void)
{
	std::list<AModule*>::iterator it = this->_moduleList.begin();
	while (it != this->_moduleList.end())
	{
		delete *it;
		it++;
	}
	return ;
}

void		AGraphical::generateModuleDisplay(AModule const &src) {
	DataStruct 			dataCpy;
	unsigned int		value = 0;
	while (true) {
		dataCpy = src.getData(value++);
		if (dataCpy.getDataAddr() == NULL && dataCpy.getDataType() != NODISP) {
			break ;
		}
		switch (dataCpy.getDataType()) {
			case CHAR_PTR:
			switch (dataCpy.getDisplayType()) {
					case STRING:
						generateStringDisplay(autoCast(reinterpret_cast<char *>(dataCpy.getDataAddr())), dataCpy.getVarLabel(), src);
						delete[] reinterpret_cast<char *>(dataCpy.getDataAddr());
					break;
					default:
						break;
				}
			break;
			case INT:
				switch (dataCpy.getDisplayType()) {
					case VALUE:
						generateValDisplay(autoCast(reinterpret_cast<int *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<int *>(dataCpy.getDataAddr());
					break;
					case GRAPH:
						generateCurveDisplay(autoCast(reinterpret_cast<int *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<int *>(dataCpy.getDataAddr());
					default:
						break;
				}
			break;
			case LONGINT:
				switch (dataCpy.getDisplayType()) {
					case VALUE:
						generateValDisplay(autoCast(reinterpret_cast<long int *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<long int *>(dataCpy.getDataAddr());
					break;
					case GRAPH:
						generateCurveDisplay(autoCast(reinterpret_cast<long int *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<long int *>(dataCpy.getDataAddr());
					default:
						break;
				}
			break;
			case DOUBLE:
				switch (dataCpy.getDisplayType()) {
					case VALUE:
						generateValDisplay(autoCast(reinterpret_cast<double *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<double *>(dataCpy.getDataAddr());
					break;
					case GRAPH:
						generateCurveDisplay(autoCast(reinterpret_cast<double *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<double *>(dataCpy.getDataAddr());
					default:
						break;
				}
			break;
			case UINT64:
				switch (dataCpy.getDisplayType()) {
					case VALUE:
						generateValDisplay(autoCast(reinterpret_cast<uint64_t *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<uint64_t *>(dataCpy.getDataAddr());
					break;
					case GRAPH:
						generateCurveDisplay(autoCast(reinterpret_cast<uint64_t *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<uint64_t *>(dataCpy.getDataAddr());
					default:
						break;
				}
			break;
			case UINT32:
				switch (dataCpy.getDisplayType()) {
					case VALUE:
						generateValDisplay(autoCast(reinterpret_cast<uint32_t *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<uint32_t *>(dataCpy.getDataAddr());
					break;
					case GRAPH:
						generateCurveDisplay(autoCast(reinterpret_cast<uint32_t *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<uint32_t *>(dataCpy.getDataAddr());
					default:
						break;
				}
			break;
			case SIZET:
				switch (dataCpy.getDisplayType()) {
					case VALUE:
						generateValDisplay(autoCast(reinterpret_cast<size_t *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<size_t *>(dataCpy.getDataAddr());
					break;
					case GRAPH:
						generateCurveDisplay(autoCast(reinterpret_cast<size_t *>(dataCpy.getDataAddr())[0]), dataCpy.getVarLabel(), src);
						delete reinterpret_cast<size_t *>(dataCpy.getDataAddr());
					default:
						break;
				}
			break;
			case TIME_T:
				switch (dataCpy.getDisplayType()) {
					case STRING:

					break;
					case VALUE:

					break;
					default:
						break;
				}
			break;
			case TIMEVAL:
				switch (dataCpy.getDisplayType()) {
					case TIME_VAL:

					break;
					default:
						break;
				}
			case XSWUSAGE:
				switch (dataCpy.getDisplayType()) {
					case XSW_USAGE:

					break;
					default:
						break;
				}
			break;
			case VMSTAT64:
				switch (dataCpy.getDisplayType()) {
					case VM_STAT64:

					break;
					default:
						break;
				}
			break;
			case NODISP:
				break;
			default:
				break;
			//ADD THROW /!\ <-NONDISPLAYABLE
		}
	}
}


bool				AGraphical::getIsActive(void)	const						{ return (this->_isActive); }
unsigned int		AGraphical::getX(void)			const						{ return (this->_x); }
unsigned int		AGraphical::getY(void)			const						{ return (this->_y); }
std::string			AGraphical::getName(void)		const						{ return (this->_name); }

void				AGraphical::setIsActive(bool isActive)						{ this->_isActive = isActive; }
void				AGraphical::setX(unsigned int x)							{ this->_x = x; }
void				AGraphical::setY(unsigned int y)							{ this->_y = y; }
void				AGraphical::setName(std::string name)						{ this->_name = name; }

std::list<AModule *> &AGraphical::get_moduleList()
{
	return _moduleList;
}

const char *AGraphical::NoModuleException::what() const throw()
{
	return ("No Module created.");
}
