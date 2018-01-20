/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataStruct.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnoon <vnoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:52:40 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/20 16:06:29 by vnoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DataStruct.hpp"

DataStruct::DataStruct(void) : _dataAddr(NULL), _dataType(UNKNOWN_TYPE), _displayType(UNKNOWN_DISPLAY) {
    return;
}

DataStruct::DataStruct(DataStruct const & src) : _dataAddr(src.getDataAddr()), _dataType(src.getDataType()), _displayType(src.getDisplayType()) {
    return;
}
DataStruct::~DataStruct(void) {
    return ;
}

DataStruct &    DataStruct::operator=(DataStruct const & rhs) {
    this->setDataType(rhs.getDataType());
    this->setDisplayType(rhs.getDisplayType());
    return (*this);
}

void const      *DataStruct::getDataAddr(void) const    {   return (this->_dataAddr);}
E_VarType       DataStruct::getDataType(void) const     {   return (this->_dataType);}
E_DisplayType   DataStruct::getDisplayType(void) const  {   return (this->_displayType);}

void            DataStruct::setDataAddr(void * addr) {
    this->_dataAddr = addr;
}

void            DataStruct::setDataType(E_VarType VarType) {
    this->_dataType = VarType;
}

void            DataStruct::setDisplayType(E_DisplayType displayType) {
    this->_displayType = displayType;
}