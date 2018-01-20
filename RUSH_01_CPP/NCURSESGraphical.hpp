/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCURSESGraphical.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:24:20 by jpiniau           #+#    #+#             */
/*   Updated: 2018/01/20 22:24:23 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESGRAPHICAL
# define NCURSESGRAPHICAL

//#include "AGraphical.hpp"
#include <ncurses.h>

class NCURSESGraphical
{
	public:
		NCURSESGraphical(void);
		~NCURSESGraphical(void);

		bool		getQuit(void) const ;
		void		setQuit(bool const & value);

	private:
		WINDOW		*_winCPU;
		WINDOW		*_winOS;
		WINDOW		*_winUser;
		WINDOW		*_winRAM;
		WINDOW		*_winNetwork;
		WINDOW		*_winClock;
		bool		_quit;

		NCURSESGraphical(NCURSESGraphical const & src);
		
		NCURSESGraphical const & operator=(NCURSESGraphical const & rhs);
};

#endif
