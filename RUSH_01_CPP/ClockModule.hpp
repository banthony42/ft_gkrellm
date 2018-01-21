/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClockModule.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnoon <vnoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:55:23 by vnoon             #+#    #+#             */
/*   Updated: 2018/01/21 14:09:31 by vnoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOCKMODULE_HPP
# define CLOCKMODULE_HPP

# include "AModule.hpp"

# include <ctime>
# include <time.h>

class ClockModule : public AModule {
    private:
    char            *_date;
    char            *_timebuff;
    time_t          _timeS;
    struct tm       _timeval;

    ClockModule(ClockModule const & src);
    ClockModule(void);
    ClockModule const & operator=(ClockModule const & rhs);

    public:
    ClockModule(bool isActive, int ID, std::string name, int position, int len);
    virtual ~ClockModule(void);
    
    virtual void                updateSysInfo(void);
    virtual DataStruct const    getData(unsigned int n) const;

    char                        *getDate(void) const;
    char                        *getTimeBuff(void) const;

    void                        setDate(char *date);
    void                        setTimeBuff(char *timebuff);
    void                        setTimeS(time_t timeS);
    void                        setTimeval(struct tm timeval);    
};

#endif