/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnoon <vnoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:21:10 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/20 12:44:07 by vnoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

#include "DataStruct.hpp"

class IMonitorDisplay {
    virtual void updateSysInfo(void) = 0;
    virtual DataStruct getData(unsigned int n);
};

#endif