/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserModule.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 23:19:57 by banthony          #+#    #+#             */
/*   Updated: 2018/01/20 23:19:57 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERMODULE_HPP
#define USERMODULE_HPP

#include "AModule.hpp"

#define HOST_NAME_MAX 256       //sensé etre definit dans #include <limits.h>
#define LOGIN_NAME_MAX 256      //sensé etre definit dans #include <limits.h>

class UserModule: public AModule {

private:
    char    *_hostname;
    char    *_username;

    UserModule(void);
    UserModule(UserModule const &copy);
    UserModule const &operator=(UserModule const &copy);
public:

    UserModule(bool isActive, int ID, std::string name, int position, int len);
    virtual ~UserModule(void);
    virtual void        updateSysInfo(void);
    virtual DataStruct  const getData(unsigned int n) const;

    char *get_hostname() const;

    char *get_username() const;
};


#endif //RUSH_01_CPP_USERMODULE_HPP