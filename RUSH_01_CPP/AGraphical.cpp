/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AGraphical.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 11:26:26 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 15:03:35 by jrouthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AGraphical.hpp"

AGraphical::AGraphical(void) : IMonitorDisplay(),
	_isActive(false),
	_x(0),
	_y(0),
	_name("Unnamed AGraphical")
{
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
	return ;
}

void		AGraphical::generateModuleDisplay(AModule const &src) {
	DataStruct 			dataCpy;
	unsigned int		value = 0;
	while (true) {
		dataCpy = src.getData(value++);
		if (dataCpy.getDataAddr() == NULL)
			break ;
		switch (dataCpy.getDataType()) {
			case CHAR_PTR:
			switch (dataCpy.getDisplayType()) {
					case STRING:

					break;
					default:
						break;
				}
			break;
			case INT:
				switch (dataCpy.getDisplayType()) {
					case STRING:

					break;
					case VALUE:

					break;
					case GRAPH:
					default:
						break;
				}
			break;
			case LONGINT:
				switch (dataCpy.getDisplayType()) {
					case STRING:

					break;
					case VALUE:

					break;
					case GRAPH:

					break;
					default:
						break;
				}
			break;
			case DOUBLE:
				switch (dataCpy.getDisplayType()) {
					case STRING:

					break;
					case VALUE:

					break;
					case GRAPH:

					break;
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
			case UINT64:
				switch (dataCpy.getDisplayType()) {
					case STRING:

					break;
					case VALUE:

					break;
					case GRAPH:

					break;
					default:
						break;
				}
			break;
			case UINT32:
				switch (dataCpy.getDisplayType()) {
					case STRING:

					break;
					case VALUE:

					break;
					case GRAPH:

					break;
					default:
						break;
				}
			break;
			case SIZET:
				switch (dataCpy.getDisplayType()) {
					case STRING:

					break;
					case VALUE:

					break;
					case GRAPH:

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
			break;
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
