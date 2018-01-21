/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserModule.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:39:13 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 15:07:51 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserModule.hpp"

UserModule::UserModule(UserModule const &copy): AModule(copy) {
    *this = copy;
}

UserModule::UserModule(void): AModule() {
    return ;
}

UserModule const &UserModule::operator=(UserModule const &copy) {
    return copy;
}

UserModule::UserModule(bool isActive, int ID, std::string name, int position, int len):
        AModule(isActive, ID, name, position, len), _hostname(0), _username(0) {
    return ;
}

UserModule::~UserModule(void) {
    if (this->_hostname != 0)
        delete [] this->_hostname;
    if (this->_username != 0)
        delete [] this->_username;
    return;
}

void UserModule::updateSysInfo(void)
{
    if (this->_hostname != NULL)
        delete [] this->_hostname;
    if (this->_username != NULL)
        delete [] this->_username;

    try
    {
	    this->_hostname = new char[sizeof(char) * HOST_NAME_MAX];
        this->_username = new char[sizeof(char) * LOGIN_NAME_MAX];

        if (gethostname(this->_hostname, HOST_NAME_MAX) < 0)
            throw std::exception();
        if (getlogin_r(this->_username, LOGIN_NAME_MAX) != 0) // existe aussi getlogin() qui renvoi une chaine alloué, surement plus pratique d'ailleurs
            throw std::exception();

    }
    catch (std::exception const &e)
    {
        std::cout << "HOST_USER_ERROR:" << e.what() << std::endl;
    }
}

DataStruct const UserModule::getData(unsigned int n) const
{
    DataStruct dataToReturn;
    if (n == 0) {
        if (this->_hostname == 0)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_hostname) * sizeof(char)];
        std::strcpy(ptr, this->_hostname);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        dataToReturn.setVarLabel("Hostname");
        return (dataToReturn);
    }
    else if (n == 1) {
        if (this->_username == 0)
            return (dataToReturn);
        char *ptr = new char[std::strlen(this->_username) * sizeof(char)];
        std::strcpy(ptr, this->_username);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(CHAR_PTR);
        dataToReturn.setDisplayType(STRING);
        dataToReturn.setVarLabel("Username");
        return (dataToReturn);
    }
    return (dataToReturn);
}

char *UserModule::get_hostname() const
{
    return _hostname;
}

char *UserModule::get_username() const
{
    return _username;
}
