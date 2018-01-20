/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:13:36 by mgras             #+#    #+#             */
/*   Updated: 2018/01/20 11:36:21 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <net/route.h>
#include <sys/sysctl.h>
#include <iostream>
#include <net/if.h>
#include <sstream>
#include <time.h>

int		main(void)
{
	int			mib[6];
	size_t		len;
	long int 	ipackets = 0;
	long int 	opackets = 0;
	long int 	ibytes = 0;
	long int 	obytes = 0;
	char		*buf;
	char		*lim;
	char 		*next;
	struct 		if_msghdr *ifm;

	mib[0]= CTL_NET;		// networking subsystem
	mib[1]= PF_ROUTE;		// type of information
	mib[2]= 0;				// protocol (IPPROTO_xxx)
	mib[3]= 0;				// address family
	mib[4]= NET_RT_IFLIST2;	// operation
	mib[5]= 0;

	sysctl(mib, 6, NULL, &len, NULL, 0);
	buf = new char[(sizeof(char) * len)];
	sysctl(mib, 6, buf, &len, NULL, 0);
	lim = buf + len;
	for (next = buf; next < lim;) {
		ifm = (struct if_msghdr *)next;
		next += ifm->ifm_msglen;

		if (ifm->ifm_type == RTM_IFINFO2) {
			struct if_msghdr2 *if2m = (struct if_msghdr2 *)ifm;

			if(if2m->ifm_data.ifi_type!=18) {
				opackets	+= if2m->ifm_data.ifi_opackets;
				ipackets	+= if2m->ifm_data.ifi_ipackets;
				obytes		+= if2m->ifm_data.ifi_obytes;
				ibytes		+= if2m->ifm_data.ifi_ibytes;
			}
		}
	}
	std::cout << "(double)\tTotal number of Bytes In:\t" << static_cast<double>(ibytes) / 1000000000.0 << std::endl;
	std::cout << "(double)\tTotal number of Bytes Out:\t" << static_cast<double>(obytes) / 1000000000.0 << std::endl;
	std::cout << "(long int)\tTotal number of Packets In:\t" << ipackets << std::endl;
	std::cout << "(long int)\tTotal number of Bytes Out:\t" << opackets << std::endl;
	delete buf;
	return (0);
}