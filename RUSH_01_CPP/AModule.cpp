/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AModule.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 13:18:18 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/20 19:49:49 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AModule.hpp"

AModule::AModule(AModule const & rhs) {
    *this = rhs;
    return;
}

AModule::AModule(void) {
    return;
}

AModule const &     AModule::operator=(AModule const & rhs) {
    return (rhs);
}

bool                AModule::compareOrder (const AModule & first, const AModule & second){
    return (first.getPosition() < second.getPosition());
}

AModule::AModule(bool isActive, int ID, std::string name, int position, int len) :
        _isActive(isActive), _ID(ID), _name(name), _position(position), _len(len) {
    return;
}

AModule::~AModule(void) {
    return;
}

const char * AModule::NothingToGetException::what() const throw() {
    return ("This object can't return any value.");
}

const char * AModule::NothingToUpDateException::what() const throw() {
    return ("This object can't update any value.");
}

void                AModule::updateSysInfo(void) {
    throw NothingToUpDateException();
}

DataStruct const    AModule::getData(unsigned int n) const {
    unsigned int    val = n;
    if (val == n)
        val++;
    throw NothingToGetException();
    return (DataStruct());
}

bool                AModule::getIsActive(void) const    {   return (this->_isActive);}
int                 AModule::getID(void) const          {   return (this->_ID);}
std::string         AModule::getName(void) const        {   return (this->_name);}
int                 AModule::getPosition(void) const    {   return (this->_position);}
int                 AModule::getLen(void) const         {   return (this->_len);}

void                AModule::setIsActive(bool val) {
    this->_isActive = val;
}

void                AModule::setID(int id) {
    this->_ID = id;
}

void                AModule::setName(std::string name) {
    this->_name = name;
}

void                AModule::setPosition(int pos) {
    this->_position = pos;
}

void                AModule::setLen(int len) {
    this->_len = len;
}