/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataStruct.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:40:28 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/21 13:45:52 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCT_HPP
# define DATASTRUCT_HPP

#include <cstddef>

enum    E_VarType {UNKNOWN_TYPE, CHAR_PTR, INT, LONGINT, DOUBLE, TIME_T, UINT64, UINT32, SIZET, TIMEVAL, XSWUSAGE, VMSTAT64};
enum    E_DisplayType {UNKNOWN_DISPLAY, STRING, VALUE, GRAPH, TIME_VAL, XSW_USAGE, VM_STAT64};

class       DataStruct {
    private:
    void            *_dataAddr;
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