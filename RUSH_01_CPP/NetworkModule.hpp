/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkModule.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:16:58 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 14:34:08 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_MODULE_HPP
# define NETWORK_MODULE_HPP

# include "AModule.hpp"

class NetworkModule : public AModule {
	private:
		double		_bytesInDiff;
		double		_bytesOutDiff;
		long int	_packetInDiff;
		long int	_packetOutDiff;

		double		_bytesInNew;
		double		_bytesOutNew;
		long int	_packetInNew;
		long int	_packetOutNew;

		double		_bytesInOld;
		double		_bytesOutOld;
		long int	_packetInOld;
		long int	_packetOutOld;

	public:
		NetworkModule(void);
		NetworkModule(NetworkModule const &src);
		NetworkModule(bool isActive, int ID, std::string name, int position, int len);
		virtual ~NetworkModule(void);

		virtual void		updateSysInfo(void);
		virtual DataStruct	const getData(unsigned int n) const;

		double				getBytesInDiff(void) const;
		double				getBytesOutDiff(void) const;
		long int			getPacketInDiff(void) const;
		long int			getPacketOutDiff(void) const;
		double				getBytesInNew(void) const;
		double				getBytesOutNew(void) const;
		long int			getPacketInNew(void) const;
		long int			getPacketOutNew(void) const;
		double				getBytesInOld(void) const;
		double				getBytesOutOld(void) const;
		long int			getPacketInOld(void) const;
		long int			getPacketOutOld(void) const;

		void				setBytesInDiff(double bytesInDiff);
		void				setBytesOutDiff(double bytesOutDiff);
		void				setPacketInDiff(long int packetInDiff);
		void				setPacketOutDiff(long int packetOutDiff);
		void				setBytesInNew(double bytesInNew);
		void				setBytesOutNew(double bytesOutNew);
		void				setPacketInNew(long int packetInNew);
		void				setPacketOutNew(long int packetOutNew);
		void				setBytesInOld(double bytesInOld);
		void				setBytesOutOld(double bytesOutOld);
		void				setPacketInOld(long int packetInOld);
		void				setPacketOutOld(long int packetOutOld);
};

#endif