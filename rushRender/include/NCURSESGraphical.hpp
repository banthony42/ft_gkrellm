/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCURSESGraphical.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:24:20 by jpiniau           #+#    #+#             */
/*   Updated: 2018/01/21 20:36:30 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESGRAPHICAL_HPP
# define NCURSESGRAPHICAL_HPP

#include "AGraphical.hpp"
#include <ncurses.h>
#include <ctime>
#include <iostream>

class NCURSESGraphical : public AGraphical
{
	public:
		NCURSESGraphical(void);
		~NCURSESGraphical(void);

		virtual void				generateCurveDisplay(float lastPoint, std::string label, AModule const &mod);
		virtual void				generateValDisplay(float val, std::string label, AModule const &mod);
		virtual void				generateStringDisplay(std::string str, std::string label, AModule const &mod);

		void						updateVisual(void);
		void						refreshVisual(void);
	
		std::string	getCpuGraph(void) const ;
		std::string	getRamGraph(void) const ;
		std::string	getNetworkGraph(void) const ;
		virtual bool		isOpen(void);
		virtual void		close(void);
		void		setQuit(bool const & value);

	private:
		WINDOW			*_winCPU;
		WINDOW			*_winOS;
		WINDOW			*_winUser;
		WINDOW			*_winRAM;
		WINDOW			*_winNetwork;
		WINDOW			*_winClock;
		std::string     *_cpuGraph;
		std::string     *_osGraph;
		std::string     *_userGraph;
		std::string     *_ramGraph;
		std::string     *_networkGraph;
		std::string     *_clockGraph;
		bool			_open;
		int				_x;
		int				_y;

		NCURSESGraphical(NCURSESGraphical const & src);
		
		NCURSESGraphical const &	operator=(NCURSESGraphical const & rhs);
		std::string	*				initGraph(void);
		void						updateGraph(std::string * graph, int val);
};

#endif
