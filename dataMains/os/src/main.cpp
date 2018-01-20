/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 13:24:46 by mgras             #+#    #+#             */
/*   Updated: 2018/01/20 13:50:21 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/utsname.h>
#include <iostream>
#include <cstring> //strcpy

int		main(void)
{
	struct utsname	sys;
	char			*os;
	char			*nodeName;
	char			*release;
	char			*version;
	char			*machine;

	try
	{
		if (uname(&sys) < 0)
			throw std::exception();
		os = new char[sizeof(sys.sysname)];
		strcpy(os, sys.sysname);
		nodeName = new char[sizeof(sys.nodename)];
		strcpy(nodeName, sys.nodename);
		release = new char[sizeof(sys.release)];
		strcpy(release, sys.release);
		version = new char[sizeof(sys.version)];
		strcpy(version, sys.version);
		machine = new char[sizeof(sys.machine)];
		strcpy(machine, sys.machine);

		std::cout << "(char*)\t\tOS:\t\t" << os << std::endl;
		std::cout << "(char*)\t\tnodename:\t" << nodeName << std::endl;
		std::cout << "(char*)\t\trelease:\t" << release << std::endl;
		std::cout << "(char*)\t\tversion:\t" << version << std::endl;
		std::cout << "(char*)\t\tarch:\t\t" << machine << std::endl;
		delete []os;
		delete []release;
		delete []version;
		delete []machine;
	}
	catch (std::exception const &e)
	{
		std::cout << "OS_INFO_ERROR:" << e.what() << std::endl;
	}
	return (0);
}