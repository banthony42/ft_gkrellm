/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OsModule.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:17:04 by banthony          #+#    #+#             */
/*   Updated: 2018/01/21 14:33:46 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OsModule.hpp"

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
        AModule(isActive, ID, name, position, len), _os(0), _nodeName(0), _release(0), _version(0), _machine(0) {
    return ;
}

OsModule::~OsModule(void) {
    if (this->_os != 0)
        delete [] this->_os;
    if (this->_nodeName != 0)
        delete [] this->_nodeName;
    if (this->_release != 0)
        delete [] this->_release;
    if (this->_version != 0)
        delete [] this->_version;
    if (this->_machine != 0)
        delete [] this->_machine;
    return ;
}

void OsModule::updateSysInfo(void)
{
    struct utsname	sys;

    if (this->_os != 0)
        delete [] this->_os;
    if (this->_nodeName != 0)
        delete [] this->_nodeName;
    if (this->_release != 0)
        delete [] this->_release;
    if (this->_version != 0)
        delete [] this->_version;
    if (this->_machine != 0)
        delete [] this->_machine;
    try
    {
        if (uname(&sys) < 0)
            throw std::exception();
        this->_os = new char[sizeof(sys.sysname)];
        std::strncpy(this->_os, sys.sysname, sizeof(sys.sysname));

        this->_nodeName = new char[sizeof(sys.nodename)];
        std::strncpy(this->_nodeName, sys.nodename, sizeof(sys.nodename));

        this->_release = new char[sizeof(sys.release)];
        std::strncpy(this->_release, sys.release, sizeof(sys.release));

        this->_version = new char[sizeof(sys.version)];
        std::strncpy(this->_version, sys.version, sizeof(sys.version));

        this->_machine = new char[sizeof(sys.machine)];
        std::strncpy(this->_machine, sys.machine, sizeof(sys.machine));
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
        if (this->_os == 0)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_os) * sizeof(char)];
        std::strcpy(ptr, this->_os);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        return (dataToReturn);
    }
    else if (n == 1) {
        if (this->_nodeName == 0)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_nodeName) * sizeof(char)];
        std::strcpy(ptr, this->_nodeName);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        return (dataToReturn);
    }
    else if (n == 2) {
        if (this->_release == 0)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_release) * sizeof(char)];
        std::strcpy(ptr, this->_release);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        return (dataToReturn);
    }
    else if (n == 3) {
        if (this->_version == 0)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_version) * sizeof(char)];
        std::strcpy(ptr, this->_version);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        return (dataToReturn);
    }
    else if (n == 4) {
        if (this->_machine == 0)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_machine) * sizeof(char)];
        std::strcpy(ptr, this->_machine);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
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
