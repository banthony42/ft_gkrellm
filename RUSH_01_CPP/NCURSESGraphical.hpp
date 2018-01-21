/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCURSESGraphical.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:24:20 by jpiniau           #+#    #+#             */
/*   Updated: 2018/01/21 15:50:18 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESGRAPHICAL_HPP
# define NCURSESGRAPHICAL_HPP

#include "AGraphical.hpp"
#include <ncurses.h>
#include <ctime>
#include <iostream>

class NCURSESGraphical// : public AGraphical
{
	public:
		NCURSESGraphical(void);
		~NCURSESGraphical(void);

		virtual void				generateCurveDisplay(float lastPoint, std::string label);
		virtual void				generateValDisplay(float val, std::string label);
		virtual void				generateStringDisplay(std::string str, std::string label);

		void						updateVisual(void);
		void						refreshVisual(void);
	
		std::string	getCpuGraph(void) const ;
		std::string	getRamGraph(void) const ;
		std::string	getNetworkGraph(void) const ;
		bool		getQuit(void) const ;
		void		setQuit(bool const & value);

	private:
		WINDOW			*_winCPU;
		WINDOW			*_winOS;
		WINDOW			*_winUser;
		WINDOW			*_winRAM;
		WINDOW			*_winNetwork;
		WINDOW			*_winClock;
		std::string     *_cpuGraph;
		std::string     *_ramGraph;
		std::string     *_networkGraph;
		bool			_quit;

		NCURSESGraphical(NCURSESGraphical const & src);
		
		NCURSESGraphical const &	operator=(NCURSESGraphical const & rhs);
		std::string	*				initGraph(void);
		void						updateGraph(std::string * graph, int val);
};

#endif
