/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OsModule.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:17:01 by banthony          #+#    #+#             */
/*   Updated: 2018/01/20 22:17:01 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OSMODULE_HPP
#define OSMODULE_HPP

#include "AModule.hpp"

class OsModule: public AModule {

private:
    char    *_os;
    char    *_nodeName;
    char    *_release;
    char    *_version;
    char    *_machine;

    OsModule(void);

    OsModule(OsModule const &copy);
    OsModule const &operator=(OsModule const &copy);
public:

    OsModule(bool isActive, int ID, std::string name, int position, int len);
    virtual ~OsModule(void);
    virtual void        updateSysInfo(void);
    virtual DataStruct  const getData(unsigned int n) const;

    char *get_os() const;

    char *get_nodeName() const;

    char *get_release() const;

    char *get_version() const;

    char *get_machine() const;

};


#endif //RUSH_01_CPP_OSMODULE_HPP