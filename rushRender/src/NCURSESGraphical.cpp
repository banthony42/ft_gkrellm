/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCURSESGraphical.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:24:39 by jpiniau           #+#    #+#             */
/*   Updated: 2018/01/21 22:30:13 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "NCURSESGraphical.hpp"
#include "../include/AModule.hpp"
#include "../include/NCURSESGraphical.hpp"

NCURSESGraphical::NCURSESGraphical(void) : AGraphical()
{
	std::list<AModule*>::iterator it;

	initscr();
	noecho();
	curs_set(0);

	nodelay(stdscr, TRUE);
	start_color();
	init_color(COLOR_RED, 100, 200, 400);
	init_pair(1, COLOR_CYAN, COLOR_RED);

	_x = 0;
	_y = 0;

	for(it = this->get_moduleList().begin(); it != this->get_moduleList().end(); ++it)
	{
		if ((*it)->getIsActive() == true)
		{
			if ((*it)->getName() == "CPU")
			{
				{
					_winCPU = newwin(20, 102, _y, _x);
					nodelay(_winCPU, TRUE);
					wbkgd(_winCPU, COLOR_PAIR(1));
					box(_winCPU, 0, 0);
					//_cpuGraph = initGraph();
					mvwprintw(_winCPU, 1, 49, "CPU");
					if (_x == 102)
					{
						_x = 0;
						_y += 20;
					}
					else
					{
						_x = 102; 
					}
				}
			}
			else if ((*it)->getName() == "OS")
			{	
				_winOS = newwin(20, 102, _y, _x);
				nodelay(_winOS, TRUE);
				wbkgd(_winOS, COLOR_PAIR(1));
				box(_winOS, 0, 0);
				//_osGraph = initGraph();
				mvwprintw(_winOS, 1, 49, "OS");
				if (_x == 102)
				{
					_x = 0;
					_y += 20;
				}
				else
				{
					_x = 102; 
				}
			}
			else if ((*it)->getName().compare("USER") == 0)
			{	
				_winUser = newwin(20, 102, _y, _x);
				nodelay(_winUser, TRUE);
				wbkgd(_winUser, COLOR_PAIR(1));
				box(_winUser, 0, 0);
				//_userGraph = initGraph();
				mvwprintw(_winUser, 1, 49, "USER");
				if (_x == 102)
				{
					_x = 0;
					_y += 20;
				}
				else
				{
					_x = 102; 
				}
			}
			else if ((*it)->getName().compare("RAM") == 0)
			{	
				_winRAM = newwin(20, 102, _y, _x);
				nodelay(_winRAM, TRUE);
				wbkgd(_winRAM, COLOR_PAIR(1));
				box(_winRAM, 0, 0);
				//_ramGraph = initGraph();
				mvwprintw(_winRAM, 1, 49, "RAM");
				if (_x == 102)
				{
					_x = 0;
					_y += 20;
				}
				else
				{
					_x = 102; 
				}
			}
			else if ((*it)->getName().compare("NET") == 0)
			{	
				_winNetwork = newwin(20, 102, _y, _x);
				nodelay(_winNetwork, TRUE);
				wbkgd(_winNetwork, COLOR_PAIR(1));
				box(_winNetwork, 0, 0);
				//_networkGraph = initGraph();
				mvwprintw(_winNetwork, 1, 49, "NETWORK");
				if (_x == 102)
				{
					_x = 0;
					_y += 20;
				}
				else
				{
					_x = 102; 
				}
			}
			else if ((*it)->getName().compare("CLOCK") == 0)
			{	
				_winClock = newwin(20, 102, _y, _x);
				nodelay(_winClock, TRUE);
				wbkgd(_winClock, COLOR_PAIR(1));
				box(_winClock, 0, 0);
				//_cpuGraph = initGraph();
				mvwprintw(_winClock, 1, 49, "CLOCK");
				if (_x == 102)
				{
					_x = 0;
					_y += 20;
				}
				else
				{
					_x = 102; 
				}
			}
		}
	}	

	refresh();
	for (it = this->get_moduleList().begin();it != this->get_moduleList().end();++it)
	{
		if ((*it)->getIsActive() == true)
		{
			if ((*it)->getName().compare("CPU") == 0)
				wrefresh(_winCPU);
			else if ((*it)->getName().compare("OS") == 0)
				wrefresh(_winOS);
			else if ((*it)->getName().compare("USER") == 0)
				wrefresh(_winUser);
			else if ((*it)->getName().compare("RAM") == 0)
				wrefresh(_winRAM);
			else if ((*it)->getName().compare("NET") == 0)
				wrefresh(_winNetwork);
			else if ((*it)->getName().compare("CLOCK") == 0)
				wrefresh(_winClock);
		}	
	}

	_open = true;
}

NCURSESGraphical::NCURSESGraphical(NCURSESGraphical const & src)  : AGraphical(src)
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
	static clock_t	this_time = clock();
	static clock_t	last_time = this_time;
	static double	time_counter = 0;
	int				ch = -1;

	this_time = clock();
	time_counter += (double) (this_time - last_time);
	last_time = this_time;
	if (time_counter > (double)( (0.1) * CLOCKS_PER_SEC))
	{
		time_counter -= (double)( (0.1) * CLOCKS_PER_SEC);
		std::list<AModule*>::iterator it = this->get_moduleList().begin();
		while (it != this->get_moduleList().end())
		{
			(*it)->updateSysInfo();
			it++;
		}
	}

	ch = wgetch(stdscr);
	if (ch == 27)
		this->_open = false;
}

void						NCURSESGraphical::refreshVisual(void)
{
	std::list<AModule*>::iterator it;
	refresh();
	for (it = this->get_moduleList().begin();it != this->get_moduleList().end();++it)
	{
		if ((*it)->getIsActive() == true)
		{
			generateModuleDisplay(**it);
			if ((*it)->getName().compare("CPU") == 0)
			{
				wbkgd(_winCPU, COLOR_PAIR(1));
				box(_winCPU, 0, 0);
				wrefresh(_winCPU);
			}
			else if ((*it)->getName().compare("OS") == 0) {
				wbkgd(_winOS, COLOR_PAIR(1));
				box(_winOS, 0, 0);
				wrefresh(_winOS);
			}
			else if ((*it)->getName().compare("USER") == 0)
			{
				wbkgd(_winUser, COLOR_PAIR(1));
				box(_winUser, 0, 0);
				wrefresh(_winUser);
			}
			else if ((*it)->getName().compare("RAM") == 0)
			{
				wbkgd(_winRAM, COLOR_PAIR(1));
				box(_winRAM, 0, 0);
				wrefresh(_winRAM);
			}
			else if ((*it)->getName().compare("NET") == 0)
			{
				wbkgd(_winNetwork, COLOR_PAIR(1));
				box(_winNetwork, 0, 0);
				wrefresh(_winNetwork);
			}
			else if ((*it)->getName().compare("CLOCK") == 0)
			{
				wbkgd(_winClock, COLOR_PAIR(1));
				box(_winClock, 0, 0);
				wrefresh(_winClock);
			}
		}	
	}
}

void						NCURSESGraphical::generateCurveDisplay(float lastPoint, std::string label, AModule const &mod)
{
	/*
	// definir les label //
	if (label.compare("cpu") == 0)
	updateGraph(_cpuGraph, static_cast<int>(lastPoint / 10));
	else if (label.compare("os") == 0)
	updateGraph(_osGraph, static_cast<int>(lastPoint / 10));
	else if (label.compare("user") == 0)
	updateGraph(_userGraph, static_cast<int>(lastPoint / 10));
	else if (label.compare("ram") == 0)
	updateGraph(_ramGraph, static_cast<int>(lastPoint / 10));
	else if (label.compare("network") == 0)
	updateGraph(_networkGraph, static_cast<int>(lastPoint / 10));
	else if (label.compare("clock") == 0)
	updateGraph(_clockGraph, static_cast<int>(lastPoint / 10));

	if (label.compare("cpu") == 0)
	else if (label.compare("ram") == 0)
	updateGraph(_ramGraph, static_cast<int>(lastPoint / 10));
	else if (label.compare("network") == 0)
	updateGraph(_networkGraph, static_cast<int>(lastPoint / 10));
	*/
	generateValDisplay(lastPoint, label, mod);
}

void						NCURSESGraphical::generateValDisplay(float val, std::string label, AModule const &mod)
{
	std::ostringstream os;

	os << val;
	generateStringDisplay(os.str(), label, mod);
}

void						NCURSESGraphical::generateStringDisplay(std::string str, std::string label, AModule const &mod)
{
	static int		y[6] = {0};
	static std::string	oldLabel;
	static std::string	oldModName;
	int				i = -1;

	str.insert(0, " : ");
	str.insert(0, label);
	if (mod.getName().compare("CPU") == 0)
	{
		mvwprintw(_winCPU, y[0]++, 1, str.c_str());
		if (oldLabel.compare(label) == 0 && oldModName.compare(mod.getName()) == 0)
			y[0] = 2;
		while (++i < 6)
			if (i != 0)
				y[i] = 2;
		if (y[0] == 2)
			oldLabel = label;
		oldModName = mod.getName();
	}
	if (mod.getName().compare("OS") == 0)
	{
		mvwprintw(_winOS, y[1]++, 1, str.c_str());
		if (oldLabel.compare(label) == 0 && oldModName.compare(mod.getName()) == 0)
			y[1] = 2;
		while (++i < 6)
			if (i != 1)
				y[i] = 2;
		if (y[1] == 2)
			oldLabel = label;
		oldModName = mod.getName();
	}
	if (mod.getName().compare("USER") == 0)
	{
		mvwprintw(_winUser, y[2]++, 1, str.c_str());
		if (oldLabel.compare(label) == 0 && oldModName.compare(mod.getName()) == 0)
			y[2] = 2;
		while (++i < 6)
			if (i != 2)
				y[i] = 2;
		if (y[2] == 2)
			oldLabel = label;
		oldModName = mod.getName();
	}
	if (mod.getName().compare("RAM") == 0)
	{
		mvwprintw(_winRAM, y[3]++, 1, str.c_str());
		if (oldLabel.compare(label) == 0 && oldModName.compare(mod.getName()) == 0)
			y[3] = 2;
		while (++i < 6)
			if (i != 3)
				y[i] = 2;
		if (y[3] == 2)
			oldLabel = label;
		oldModName = mod.getName();
	}
	if (mod.getName().compare("NET") == 0)
	{
		mvwprintw(_winNetwork, y[4]++, 1, str.c_str());
		if (oldLabel.compare(label) == 0 && oldModName.compare(mod.getName()) == 0)
			y[4] = 2;
		while (++i < 6)
			if (i != 4)
				y[i] = 2;
		if (y[4] == 2)
			oldLabel = label;
		oldModName = mod.getName();
	}
	if (mod.getName().compare("CLOCK") == 0)
	{
		mvwprintw(_winClock, y[5]++, 1, str.c_str());
		if (oldLabel.compare(label) == 0 && oldModName.compare(mod.getName()) == 0)
			y[5] = 2;
		while (++i < 6)
			if (i != 5)
				y[i] = 2;
		if (y[5] == 2)
			oldLabel = label;
		oldModName = mod.getName();
	}

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

bool						NCURSESGraphical::isOpen(void) {return (_open);}

void 						NCURSESGraphical::close() {
	NCURSESGraphical::~NCURSESGraphical();
}
void						NCURSESGraphical::setQuit(bool const & value)
{
	this->_open = value;
}
