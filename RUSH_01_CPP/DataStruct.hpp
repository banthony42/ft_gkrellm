/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataStruct.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnoon <vnoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:40:28 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/20 15:35:15 by vnoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCT_HPP
# define DATASTRUCT_HPP

#include <cstddef>

enum    E_VarType {UNKNOWN_TYPE, CHAR, CHAR_PTR, UCHAR, INT, UINT, LONGINT, ULONGINT, DOUBLE, TIME_T, TM};
enum    E_DisplayType {UNKNOWN_DISPLAY, STRING, VALUE, GRAPH};

class       DataStruct {
    private:
    void const      *_dataAddr;
    E_VarType       _dataType;
    E_DisplayType   _displayType;
    public:
    DataStruct(void);
    DataStruct(DataStruct const & src);
    ~DataStruct(void);
    DataStruct &    operator=(DataStruct const & rhs);

    void            *getDataAddr(void) const;
    E_VarType       getDataType(void) const;
    E_DisplayType   getDisplayType(void) const;

    void            setDataAddr(void * addr);
    void            setDataType(E_VarType VarType);
    void            setDisplayType(E_DisplayType displayType);
};

#endif