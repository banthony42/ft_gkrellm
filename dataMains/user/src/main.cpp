/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 13:37:26 by mgras             #+#    #+#             */
/*   Updated: 2018/01/20 13:53:20 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>

#include <unistd.h>

#define HOST_NAME_MAX 256      //sensé etre definit dans #include <limits.h>
#define LOGIN_NAME_MAX 256     //sensé etre definit dans #include <limits.h>

int		main(void)
{
	char *hostname = new char[sizeof(HOST_NAME_MAX)];
	char *username = new char[sizeof(LOGIN_NAME_MAX)];

	try
	{
		if (gethostname(hostname, HOST_NAME_MAX) < 0)
			throw std::exception();
		if (getlogin_r(username, LOGIN_NAME_MAX) != 0) // existe aussi getlogin() qui renvoi une chaine alloué, surement plus pratique d'ailleurs
			throw std::exception();
		std::cout << "(char*)\t\tHostname:\t\t" << hostname << std::endl;
		std::cout << "(char*)\t\tUsername:\t\t" << username << std::endl;
		delete []hostname;
		delete []username;
	}
	catch (std::exception const &e)
	{
		std::cout << "HOST_USER_ERROR:" << e.what() << std::endl;
	}
}