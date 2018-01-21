/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataStruct.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:40:28 by vnoon             #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2018/01/21 14:35:51 by mgras            ###   ########.fr       */
=======
/*   Updated: 2018/01/21 14:29:05 by mgras            ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCT_HPP
# define DATASTRUCT_HPP

<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes

/*clock module*/
# include <ctime>

<<<<<<< Updated upstream
/*ram module*/
# include <sys/types.h>
# include <sys/sysctl.h>
# include <mach/vm_statistics.h>
# include <mach/mach_host.h>

/*cpu module*/
# include <sys/types.h>
# include <sys/sysctl.h>
# include <mach/mach_host.h>
# include <stdlib.h>
=======
/*User module*/
# include <zconf.h>

/*ram module*/
# include <mach/mach_host.h>
>>>>>>> Stashed changes

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