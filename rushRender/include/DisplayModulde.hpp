/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplayModulde.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:42:43 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 16:57:29 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_MODULE_HPP
# define DISPLAY_MODULE_HPP

# include "AModule.hpp"

class DisplayModule : public Amodule() {
	private:
		uint32_t	_maindisplayId;
		bool		_isStereo;
		uint32_t	_modelNumber;
		int			_screenWidth;
		int			_screenHeigth;
		uint32_t	_vendorNumber;

	public:
		DisplayModule(DisplayModule const & src);
		DisplayModule(void);
		DisplayModule const & operator=(DisplayModule const & rhs);
		DisplayModule(bool isActive, int ID, std::string name, int position, int len);
		~DisplayModule(void);

		virtual void				updateSysInfo(void);
    	virtual DataStruct const	getData(unsigned int n) const;

		void						setMaindisplayId(uint32_t maindisplayId);
		void						setIsStereo(bool isStereo);
		void						setModelNumber(uint32_t modelNumber);
		void						setScreenWidth(int screenWidth);
		void						setScreenHeigth(int screenHeigth);
		void						setVendorNumber(uint32_t vendorNumber);

		uint32_t					getMaindisplayId(void)	const;
		bool						getIsStereo(void)		const;
		uint32_t					getModelNumber(void)	const;
		int							getScreenWidth(void)	const;
		int							getScreenHeigth(void)	const;
		uint32_t					getVendorNumber(void)	const;
};

#endif