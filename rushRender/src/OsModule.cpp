/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OsModule.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:39:13 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 19:17:48 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/utsname.h>
#include "OsModule.hpp"
#include "../include/DataStruct.hpp"

OsModule::OsModule(OsModule const &copy):AModule(copy) {
    *this = copy;
}

OsModule::OsModule(void): AModule() {
    return ;
}

OsModule const &OsModule::operator=(OsModule const &copy) {
    return copy;
}

OsModule::OsModule(bool isActive, int ID, std::string name, int position, int len):
        AModule(isActive, ID, name, position, len), _os(NULL), _nodeName(NULL), _release(NULL), _version(NULL), _machine(NULL) {
    return ;
}

OsModule::~OsModule(void) {
    if (this->_os != NULL)
        delete [] this->_os;
    if (this->_nodeName != NULL)
        delete [] this->_nodeName;
    if (this->_release != NULL)
        delete [] this->_release;
    if (this->_version != NULL)
        delete [] this->_version;
    if (this->_machine != NULL)
        delete [] this->_machine;
    return ;
}

void OsModule::updateSysInfo(void)
{
    if (this->_os != NULL)
        delete [] this->_os;
    if (this->_nodeName != NULL)
        delete [] this->_nodeName;
    if (this->_release != NULL)
        delete [] this->_release;
    if (this->_version != NULL)
        delete [] this->_version;
    if (this->_machine != NULL)
        delete [] this->_machine;
    try
    {
		struct utsname	sys;
        if (uname(&sys) < 0)
            throw std::exception();
        this->_os = new char[sizeof(char) * 256];
        std::strncpy(this->_os, sys.sysname, sizeof(char) * std::strlen(sys.sysname));

        this->_nodeName = new char[sizeof(char) * 256];
        std::strncpy(this->_nodeName, sys.nodename, sizeof(char) * std::strlen(sys.nodename));

        this->_release = new char[sizeof(char) * 256];
        std::strncpy(this->_release, sys.release, sizeof(char) * std::strlen(sys.release));

/*        this->_version = new char[sizeof(char) * 256];
        std::strncpy(this->_version, sys.version, sizeof(char) * std::strlen(sys.version));
*/
        this->_machine = new char[sizeof(char) * 256];
        std::strncpy(this->_machine, sys.machine, sizeof(char) * std::strlen(sys.machine));
    }
    catch (std::exception const &e)
    {
        std::cout << "OS_INFO_ERROR:" << e.what() << std::endl;
    }
}

DataStruct const OsModule::getData(unsigned int n) const
{
    DataStruct dataToReturn;
    if (n == 0) {
        if (this->_os == NULL)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_os) * sizeof(char)];
        std::strcpy(ptr, this->_os);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        dataToReturn.setVarLabel("OS Name");
        return (dataToReturn);
    }
    else if (n == 1) {
        if (this->_nodeName == NULL)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_nodeName) * sizeof(char)];
        std::strcpy(ptr, this->_nodeName);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        dataToReturn.setVarLabel("Node Name");
        return (dataToReturn);
    }
    else if (n == 2) {
        if (this->_release == NULL)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_release) * sizeof(char)];
        std::strcpy(ptr, this->_release);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        dataToReturn.setVarLabel("Release Name");
        return (dataToReturn);
    }
    else if (n == 3) {
        if (this->_version == NULL)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_version) * sizeof(char)];
        std::strncpy(ptr, this->_version, 250);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(NODISP);
        dataToReturn.setDisplayType(STRING);
        dataToReturn.setVarLabel("Version");
        return (dataToReturn);
    }
    else if (n == 4) {
        if (this->_machine == NULL)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_machine) * sizeof(char)];
        std::strcpy(ptr, this->_machine);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        dataToReturn.setVarLabel("Machine Name");
        return (dataToReturn);
    }
    return (dataToReturn);
}

char *OsModule::get_os() const {
    return _os;
}

char *OsModule::get_nodeName() const {
    return _nodeName;
}

char *OsModule::get_release() const {
    return _release;
}

char *OsModule::get_version() const {
    return _version;
}

char *OsModule::get_machine() const {
    return _machine;
}
