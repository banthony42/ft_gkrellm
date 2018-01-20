/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 13:52:22 by mgras             #+#    #+#             */
/*   Updated: 2018/01/20 13:59:52 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include <time.h>

#include <iostream>

int		main(void)
{
	char		*date		= new char[sizeof(char) * 128];
	char		*timebuff	= new char[sizeof(char) * 128];
	time_t		timeS;
	struct tm	timeval;

	time(&timeS);
	timeval = *localtime(&timeS);
	strftime(date, sizeof(char) * 128, "%a %x", &timeval);
	strftime(timebuff, sizeof(char) * 128, "%X %Z", &timeval);
	std::cout << "(char*)\t\tDate:\t\t" << date << std::endl;
	std::cout << "(char*)\t\tTime:\t\t" << timebuff << std::endl;
	delete []timebuff;
	delete []date;
	return (0);
}