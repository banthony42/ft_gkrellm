/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AGraphical.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 11:26:26 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 11:52:30 by mgras            ###   ########.fr       */
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

bool				AGraphical::getIsActive(void)	const						{ return (this->_isActive); }
unsigned int		AGraphical::getX(void)			const						{ return (this->_x); }
unsigned int		AGraphical::getY(void)			const						{ return (this->_y); }
std::string			AGraphical::getName(void)		const						{ return (this->_name); }

void				AGraphical::setIsActive(bool isActive)						{ this->_isActive = isActive; }
void				AGraphical::setX(unsigned int x)							{ this->_x = x; }
void				AGraphical::setY(unsigned int y)							{ this->_y = y; }
void				AGraphical::setName(std::string name)						{ this->_name = name; }