/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClockModule.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:39:13 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 16:57:20 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOCKMODULE_HPP
# define CLOCKMODULE_HPP

# include "AModule.hpp"

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