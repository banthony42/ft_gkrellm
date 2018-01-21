/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:21:10 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/20 19:49:06 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

#include "DataStruct.hpp"

class IMonitorModule {
    public:
    
    virtual void updateSysInfo(void) = 0;
    virtual const DataStruct getData(unsigned int n) const = 0;
};

#endif