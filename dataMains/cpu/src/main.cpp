/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:33:29 by mgras             #+#    #+#             */
/*   Updated: 2018/01/19 19:20:45 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/sysctl.h>
#include <iostream>

int		main(void)
{
	/*Important Start*/
	uint64_t	cpuFrequency	= -1;
	int			nbCores			= -1;
	int			activeCores		= -1;
	int			cpuFamily		= -1;
	/*Important End*/
	/*Bonus material Start*/
	uint64_t	maxCoreClock	= -1;
	uint64_t	minCoreClock	= -1;
/*	uint64_t can64bits		= 0;
	uint64_t cpuSubtype		= 0;
	uint64_t cputype		= 0;
	uint64_t can64bits		= 0;*/
	/*Bonus material End*/
	size_t sizeCpuFrequency	= sizeof(cpuFrequency);
	size_t sizeNbCores		= sizeof(nbCores);
	size_t sizeActiveCores	= sizeof(activeCores);
	size_t sizeCpuFamily	= sizeof(cpuFamily);
	size_t sizeMinCoreClock	= sizeof(minCoreClock);
	size_t sizeMaxCoreClock	= sizeof(maxCoreClock);


	if (sysctlbyname("hw.cpufrequency", &cpuFrequency, &sizeCpuFrequency, NULL, 0) < 0)
		cpuFrequency = -1;
	if (sysctlbyname("hw.ncpu", &nbCores, &sizeNbCores, NULL, 0) < 0)
		nbCores = -1;
	if (sysctlbyname("hw.activecpu", &activeCores, &sizeActiveCores, NULL, 0) < 0)
		activeCores = -1;
	if (sysctlbyname("hw.cpufamily", &cpuFamily, &sizeCpuFamily, NULL, 0) < 0)
		cpuFamily = -1;
	if (sysctlbyname("hw.cpufrequency_max", &maxCoreClock, &sizeMaxCoreClock, NULL, 0) < 0)
		maxCoreClock = -1;
	if (sysctlbyname("hw.cpufrequency_min", &minCoreClock, &sizeMinCoreClock, NULL, 0) < 0)
		minCoreClock = -1;


	std::cout << "(uint64_t)\tcpuFrequency:\t" << cpuFrequency << std::endl;
	std::cout << "(int)\t\tnbCores:\t" << nbCores << std::endl;
	std::cout << "(int)\t\tactiveCores:\t" << activeCores << std::endl;
	std::cout << "(int)\t\tcpuFamily:\t" << cpuFamily << std::endl;

	std::cout << "(uint64_t)\tmaxCoreClock:\t" << maxCoreClock << std::endl;
	std::cout << "(uint64_t)\tminCoreClock:\t" << minCoreClock << std::endl;
	return (0);
}