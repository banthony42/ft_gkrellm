/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCURSESGraphical.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:24:39 by jpiniau           #+#    #+#             */
/*   Updated: 2018/01/20 22:44:23 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NCURSESGraphical.hpp"

NCURSESGraphical::NCURSESGraphical(void) //: AGraphical()
{
	initscr();
	noecho();
	curs_set(0);

	start_color();
	init_color(COLOR_RED, 100, 200, 400);
	init_pair(1, COLOR_CYAN, COLOR_RED);

	_winCPU = newwin(20, 102, 0, 0);
	_winOS = newwin(20, 102, 0, 102);
	_winUser = newwin(20, 102, 20, 0);
	_winRAM = newwin(20, 102, 20, 102);
	_winNetwork = newwin(20, 102, 40, 0);
	_winClock = newwin(20, 102, 40, 102);
	
	nodelay(_winCPU, TRUE);
	nodelay(_winOS, TRUE);
	nodelay(_winUser, TRUE);
	nodelay(_winRAM, TRUE);
	nodelay(_winNetwork, TRUE);
	nodelay(_winClock, TRUE);

	wbkgd(_winCPU, COLOR_PAIR(1));
	wbkgd(_winOS, COLOR_PAIR(1));
	wbkgd(_winUser, COLOR_PAIR(1));
	wbkgd(_winRAM, COLOR_PAIR(1));
	wbkgd(_winNetwork, COLOR_PAIR(1));
	wbkgd(_winClock, COLOR_PAIR(1));

	box(_winCPU, 0, 0);
	box(_winOS, 0, 0);
	box(_winUser, 0, 0);
	box(_winRAM, 0, 0);
	box(_winNetwork, 0, 0);
	box(_winClock, 0, 0);

	refresh();
	wrefresh(_winCPU);
	wrefresh(_winOS);
	wrefresh(_winUser);
	wrefresh(_winRAM);
	wrefresh(_winNetwork);
	wrefresh(_winClock);

	_quit = 0;
}

NCURSESGraphical::NCURSESGraphical(NCURSESGraphical const & src) //: AGraphical(src)
{
	*this = src;
}

NCURSESGraphical::~NCURSESGraphical(void)
{
	endwin();
}

NCURSESGraphical const &	NCURSESGraphical::operator=(NCURSESGraphical const & rhs)
{
	return (rhs);
}

bool						NCURSESGraphical::getQuit(void) const {return (_quit);}

void						NCURSESGraphical::setQuit(bool const & value)
{
	this->_quit = value;
}
