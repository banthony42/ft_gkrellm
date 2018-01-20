/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClockModule.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnoon <vnoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:08:33 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/20 15:51:48 by vnoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClockModule.hpp"

ClockModule::ClockModule(ClockModule const & src) : AModule(src) {
    *this = src;
}

ClockModule::ClockModule(void) : AModule() {
    return;
}

ClockModule const &         ClockModule::operator=(ClockModule const & rhs) {
    return (rhs);
}

ClockModule::ClockModule(bool isActive, int ID, std::string name, int position, int len) : 
            AModule(isActive, ID, name, position, len), _date(new char[sizeof(char) * 128]), _timebuff(new char[sizeof(char) * 128]) {
    return;
}

ClockModule::~ClockModule(void) {
    delete [] this->getDate();
    delete [] this->getTimeBuff();
    return;
}

void                        ClockModule::updateSysInfo(void) {
    time(&this->_timeS);
    this->_timeval = *localtime(&this->_timeS);
    strftime(this->getDate(), sizeof(char) * 128, "%a %x", &this->_timeval);
    strftime(this->getTimeBuff(), sizeof(char) * 128, "%X %Z", &this->_timeval);
}

//Pour ce casde figure le module ne retournera pas _timeS et _timevalcar Jessy a deja ces structures dans
//le code d'affichage.

DataStruct                  ClockModule::getData(unsigned int n) {
    DataStruct  dataToReturn;
    switch (n) {
        case 0:
            dataToReturn.setDataAddr(this->getDate());
            dataToReturn.setDataType(CHAR_PTR);
            dataToReturn.setDisplayType(STRING);
            return (dataToReturn);
        case 1:
            dataToReturn.setDataAddr(this->getTimeBuff());
            dataToReturn.setDataType(CHAR_PTR);
            dataToReturn.setDisplayType(STRING);
            return (dataToReturn);
    }
    return (dataToReturn);
}

char                        *ClockModule::getDate(void) const       {   return (this->_date);}
char                        *ClockModule::getTimeBuff(void) const   {   return (this->_timebuff);}

void                        ClockModule::setDate(char *date) {
    this->_date = date;
}

void                        ClockModule::setTimeBuff(char *timebuff) {
    this->_timebuff = timebuff;
}

void                        ClockModule::setTimeS(time_t timeS) {
    this->_timeS = timeS;
}

void                        ClockModule::setTimeval(struct tm timeval) {
    this->_timeval = timeval;
}