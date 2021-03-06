/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataStruct.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:42:59 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 19:47:33 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCT_HPP
# define DATASTRUCT_HPP

/*shared*/
# include <cstddef>
# include <iostream>
# include <cstring>
# include <sstream>
# include <time.h>

/*user module*/
# include <zconf.h>

/*os module*/
# include <sys/utsname.h>

/*network module*/
# include <net/route.h>
# include <sys/sysctl.h>
# include <net/if.h>
# include <cstddef>
# include <iostream>
# include <cstring>

/*cpu module*/
# include <sys/types.h>
# include <sys/sysctl.h>
# include <mach/mach_host.h>
# include <stdlib.h>
# include <time.h>

/*os module*/
#include <sys/utsname.h>

/*clock module*/
# include <ctime>

enum    E_VarType {UNKNOWN_TYPE, CHAR_PTR, INT, LONGINT, DOUBLE, TIME_T, UINT64, UINT32, SIZET, TIMEVAL, XSWUSAGE, VMSTAT64, NODISP};
enum    E_DisplayType {UNKNOWN_DISPLAY, STRING, VALUE, GRAPH, TIME_VAL, XSW_USAGE, VM_STAT64};

class       DataStruct {
    private:
    void            *_dataAddr;
    E_VarType       _dataType;
    E_DisplayType   _displayType;
    std::string     _varLabel;
    public:
    DataStruct(void);
    DataStruct(DataStruct const & src);
    ~DataStruct(void);
    DataStruct &    operator=(DataStruct const & rhs);

    void            *getDataAddr(void)      const;
    E_VarType       getDataType(void)       const;
    E_DisplayType   getDisplayType(void)    const;
    std::string     getVarLabel(void)       const;

    void            setDataAddr(void *addr);
    void            setDataType(E_VarType VarType);
    void            setDisplayType(E_DisplayType displayType);
    void            setVarLabel(std::string varLabel);
};

#endif