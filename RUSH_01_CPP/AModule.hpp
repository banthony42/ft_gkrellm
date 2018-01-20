/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AModule.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnoon <vnoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 13:10:41 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/20 15:12:40 by vnoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMODULE_HPP
# define AMODULE_HPP

#include "IMonitorModule.hpp"
#include <string>
#include <list>

class AModule : public IMonitorModule {
    private:
    bool        _isActive;
    int         _ID;
    std::string _name;
    int         _position;
    int         _len;
    
    bool        _compareOrder(const AModule& first, const AModule& second);

    protected:
    
    AModule(AModule const & src);
    AModule(void);
    AModule const &  operator=(AModule const & rhs);

    public:
    AModule(bool isActive, int ID, std::string name, int position, int len);
    virtual     ~AModule(void);

    class NothingToUpDateException : public std::exception {
        public:
            virtual const char * what() const throw();
    };

    class NothingToGetException : public std::exception {
        public:
            virtual const char * what() const throw();
    };

    void        sort(std::list<AModule> modules);

    virtual void updateSysInfo(void);
    virtual DataStruct getData(unsigned int n);


    //getteurs
    bool        getIsActive(void) const;
    int         getID(void) const;
    std::string getName(void) const;
    int         getPosition(void) const;
    int         getLen(void) const;

    //setteurs
    void        setIsActive(bool val);
    void        setID(int id);
    void        setName(std::string name);
    void        setPosition(int pos);
    void        setLen(int len);
};

#endif