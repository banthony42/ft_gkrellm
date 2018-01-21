/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AGraphical.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnoon <vnoon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 11:14:42 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 14:17:09 by vnoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_GRAPHICAL_HPP
# define A_GRAPHICAL_HPP

# include <list>
# include <iostream>
# include "AModule.hpp"
# include "IMonitorDisplay.hpp"

class AGraphical : public IMonitorDisplay {
	private:
		bool				_isActive;
		unsigned int		_x;
		unsigned int		_y;
		std::string			_name;
		std::list<AModule>	_moduleList;

	public:
		AGraphical(void);
		AGraphical(AGraphical const &src);
		~AGraphical(void);

		virtual void		updateVisual(void) = 0;
		virtual void		refreshVisual(void) = 0;
		virtual void		generateModuleDisplay(AModule const &src);

		virtual void		generateCurveDisplay(float lastPoint) = 0;
		virtual void		generateValDisplay(float val) = 0;
		virtual void		generateStringDisplay(std::string str) = 0;

		bool				getIsActive(void)	const;
		unsigned int		getX(void)			const;
		unsigned int		getY(void)			const;
		std::string			getName(void)		const;

		void				setIsActive(bool isActive);
		void				setX(unsigned int x);
		void				setY(unsigned int y);
		void				setName(std::string name);
};

#endif