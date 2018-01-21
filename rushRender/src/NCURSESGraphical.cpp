/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCURSESGraphical.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <jpiniau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:24:39 by jpiniau           #+#    #+#             */
/*   Updated: 2018/01/21 18:02:13 by jrouthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NCURSESGraphical.hpp"

NCURSESGraphical::NCURSESGraphical(void)// : AGraphical()
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

	_cpuGraph = initGraph();
	_ramGraph = initGraph();
	_networkGraph = initGraph();

	refresh();
	wrefresh(_winCPU);
	wrefresh(_winOS);
	wrefresh(_winUser);
	wrefresh(_winRAM);
	wrefresh(_winNetwork);
	wrefresh(_winClock);_networkGraph = initGraph();

	_quit = 0;
}

NCURSESGraphical::NCURSESGraphical(NCURSESGraphical const & src)// : AGraphical(src)
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

void						NCURSESGraphical::updateVisual(void)
{
	// ******* test ****** //
	/*
	static int		i = 0;
	static int		ii = 1;
	static clock_t	this_time = clock();
	static clock_t	last_time = this_time;
	static double	time_counter = 0;

	this_time = clock();
	time_counter += (double) (this_time - last_time);
	last_time = this_time;
	if (time_counter > (double)( (0.1) * CLOCKS_PER_SEC))
	{
		time_counter -= (double)( (0.1) * CLOCKS_PER_SEC);
		i += ii;
		if (i >= 99 || i <= 0)
			ii = -ii;

		updateGraph(_cpuGraph, i / 10);
		updateGraph(_ramGraph, i / 10);
		updateGraph(_networkGraph, i / 10);
	}
	*/
	// ********* FIN test ******//
	int				j = -1;
	int				ch = -1;

	ch = wgetch(_winCPU);
	if (ch == 27)
		_quit = true;

	while (++j < 10)
		mvwprintw(_winCPU, 5 + j, 1, _cpuGraph[j].c_str());
	j = -1;
	while (++j < 10)
		mvwprintw(_winRAM, 5 + j, 1, _ramGraph[j].c_str());
	j = -1;
	while (++j < 10)
		mvwprintw(_winNetwork, 5 + j, 1, _networkGraph[j].c_str());
	j = -1;

}

void						NCURSESGraphical::refreshVisual(void)
{
	refresh();
	wrefresh(_winCPU);
	wrefresh(_winOS);
	wrefresh(_winUser);
	wrefresh(_winRAM);
	wrefresh(_winNetwork);
	wrefresh(_winClock);
}

void						NCURSESGraphical::generateCurveDisplay(float lastPoint, std::string label)
{
	// definir les label //
	if (label.compare("cpu") == 0)
		updateGraph(_cpuGraph, static_cast<int>(lastPoint / 10));
	else if (label.compare("ram") == 0)
		updateGraph(_ramGraph, static_cast<int>(lastPoint / 10));
	else if (label.compare("network") == 0)
		updateGraph(_networkGraph, static_cast<int>(lastPoint / 10));
}

void						NCURSESGraphical::generateValDisplay(float val, std::string label)
{
	// definir les label //
	std::ostringstream os;
	std::string str;

	os << val;
	str = os.str();
	if (label.compare("cpu") == 0)
		mvwprintw(_winCPU, 18, 1, str.c_str());
	else if (label.compare("os") == 0)
		mvwprintw(_winOS, 18, 1, str.c_str());
	else if (label.compare("user") == 0)
		mvwprintw(_winUser, 18, 1, str.c_str());
	else if (label.compare("ram") == 0)
		mvwprintw(_winRAM, 18, 1, str.c_str());
	else if (label.compare("network") == 0)
		mvwprintw(_winNetwork, 18, 1, str.c_str());
	else if (label.compare("clock") == 0)
		mvwprintw(_winClock, 18, 1, str.c_str());
}

void						NCURSESGraphical::generateStringDisplay(std::string str, std::string label)
{
	// definir les label //
	if (label.compare("cpu") == 0)
		mvwprintw(_winCPU, 16, 1, str.c_str());
	else if (label.compare("os") == 0)
		mvwprintw(_winOS, 16, 1, str.c_str());
	else if (label.compare("user") == 0)
		mvwprintw(_winUser, 16, 1, str.c_str());
	else if (label.compare("ram") == 0)
		mvwprintw(_winRAM, 16, 1, str.c_str());
	else if (label.compare("network") == 0)
		mvwprintw(_winNetwork, 16, 1, str.c_str());
	else if (label.compare("clock") == 0)
		mvwprintw(_winClock, 16, 1, str.c_str());

}

std::string *				NCURSESGraphical::initGraph(void)
{
	std::string *graph = new std::string[10];
	int i = -1;
	int j = -1;

	while (++i < 10)
	{
		j = -1;
		while (++j < 100)
		{
			graph[i] = graph[i] + ".";
		}
	}
	return (graph);
}

void						NCURSESGraphical::updateGraph(std::string * graph, int val)
{
	int i = -1;
	int j = -1;


	while (++i < 10)
	{
		j = -1;
		while (++j < 99)
		{
			graph[i][j] = graph[i][j + 1];
		}
		graph[i][j] = '.';
	}
	graph[9 - val][99] = '*';
}

bool						NCURSESGraphical::getQuit(void) const {return (_quit);}

void						NCURSESGraphical::setQuit(bool const & value)
{
	this->_quit = value;
}
