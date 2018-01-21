/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataStruct.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:52:40 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/21 19:27:18 by mgras            ###   ########.fr       */
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
	this->setVarLabel(rhs.getVarLabel());
	if (this->_dataType == CHAR_PTR)
	{
		if (rhs.getDataAddr() == NULL)
			this->_dataAddr = NULL;
		else
		{
			char	*str;
			char	*ptr;

			str = reinterpret_cast<char*>(rhs.getDataAddr());
			ptr = new char[std::strlen(str) * sizeof(char)];
			std::strcpy(ptr, str);
			this->_dataAddr = ptr;
		}
	}
	else if (this->_dataType == INT)
	{
		int		val;
		int		*ptr = new int;

		val = *(reinterpret_cast<int*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else if (this->_dataType == LONGINT)
	{
		long int	val;
		long int	*ptr = new long int;

		val = *(reinterpret_cast<long int*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else if (this->_dataType == DOUBLE)
	{
		double	val;
		double	*ptr = new double;

		val = *(reinterpret_cast<double*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else if (this->_dataType == TIME_T)
	{
		time_t	val;
		time_t	*ptr = new time_t;

		val = *(reinterpret_cast<time_t*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else if (this->_dataType == UINT64)
	{
		uint64_t	val;
		uint64_t	*ptr = new uint64_t;

		val = *(reinterpret_cast<uint64_t*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else if (this->_dataType == UINT32)
	{
		uint32_t	val;
		uint32_t	*ptr = new uint32_t;

		val = *(reinterpret_cast<uint32_t*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else if (this->_dataType == SIZET)
	{
		size_t	val;
		size_t	*ptr = new size_t;

		val = *(reinterpret_cast<size_t*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else if (this->_dataType == TIMEVAL)
	{
		timeval	val;
		timeval	*ptr = new timeval;

		val = *(reinterpret_cast<timeval*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else if (this->_dataType == XSWUSAGE)
	{
		xsw_usage	val;
		xsw_usage	*ptr = new xsw_usage;

		val = *(reinterpret_cast<xsw_usage*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else if (this->_dataType == VMSTAT64)
	{
		vm_statistics64_data_t	val;
		vm_statistics64_data_t	*ptr = new vm_statistics64_data_t;

		val = *(reinterpret_cast<vm_statistics64_data_t*>(rhs.getDataAddr()));
		*ptr = val;
		this->_dataAddr = ptr;
	}
	else
		this->_dataAddr = NULL;
	return (*this);
}

void			*DataStruct::getDataAddr(void)		const				{ return (this->_dataAddr); }
E_VarType		DataStruct::getDataType(void)		const				{ return (this->_dataType); }
E_DisplayType	DataStruct::getDisplayType(void)	const				{ return (this->_displayType); }
std::string		DataStruct::getVarLabel(void)		const				{ return (this->_varLabel); }

void            DataStruct::setDataAddr(void * addr)					{ this->_dataAddr = addr; }
void            DataStruct::setDataType(E_VarType VarType)				{ this->_dataType = VarType; }
void            DataStruct::setDisplayType(E_DisplayType displayType)	{ this->_displayType = displayType;}
void			DataStruct::setVarLabel(std::string varLabel)			{ this->_varLabel = varLabel; }