/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:33:29 by mgras             #+#    #+#             */
/*   Updated: 2018/01/19 20:16:26 by mgras            ###   ########.fr       */
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
	uint32_t	cpuType			= -1;
	/*Important End*/

	/*Bonus material Start*/
	int			cpuFamily		= -1;
	uint64_t	maxCoreClock	= -1;
	uint64_t	minCoreClock	= -1;
	bool		can64bits		= 0;
	/*Bonus material End*/

	size_t sizeCpuFrequency	= sizeof(cpuFrequency);
	size_t sizeNbCores		= sizeof(nbCores);
	size_t sizeActiveCores	= sizeof(activeCores);
	size_t sizeCpuFamily	= sizeof(cpuFamily);
	size_t sizeMinCoreClock	= sizeof(minCoreClock);
	size_t sizeMaxCoreClock	= sizeof(maxCoreClock);
	size_t sizeCan64bits	= sizeof(maxCoreClock);
	size_t sizeCpuType		= sizeof(cpuType);
	//La taille des données stockées dans le pointeur seront dans leurs sizes respectives

	/*Syscalls start*/
	if (sysctlbyname("hw.cpufrequency", &cpuFrequency, &sizeCpuFrequency, NULL, 0) < 0)
		cpuFrequency = -1;
	if (sysctlbyname("hw.ncpu", &nbCores, &sizeNbCores, NULL, 0) < 0)
		nbCores = -1;
	if (sysctlbyname("hw.activecpu", &activeCores, &sizeActiveCores, NULL, 0) < 0)
		activeCores = -1;
	if (sysctlbyname("hw.hw.cputype", &cpuType, &sizeCpuType, NULL, 0) < 0)
		cpuType = -1;
	if (sysctlbyname("hw.cpufamily", &cpuFamily, &sizeCpuFamily, NULL, 0) < 0)
		cpuFamily = -1;
	if (sysctlbyname("hw.cpufrequency_max", &maxCoreClock, &sizeMaxCoreClock, NULL, 0) < 0)
		maxCoreClock = -1;
	if (sysctlbyname("hw.cpufrequency_min", &minCoreClock, &sizeMinCoreClock, NULL, 0) < 0)
		minCoreClock = -1;
	if (sysctlbyname("hw.cpu64bit_capable", &can64bits, &sizeCan64bits, NULL, 0) < 0)
		minCoreClock = -1;
	/*Syscalls End*/

	/*Test printing Start*/
	std::cout << "(uint64_t)\tcpuFrequency:\t" << cpuFrequency << std::endl;
	std::cout << "(int)\t\tnbCores:\t" << nbCores << std::endl;
	std::cout << "(int)\t\tactiveCores:\t" << activeCores << std::endl;
	std::cout << "(uint34_t)\tcpuType:\t" << cpuType << std::endl;

	std::cout << "(int)\t\tcpuFamily:\t" << cpuFamily << std::endl;
	std::cout << "(uint64_t)\tmaxCoreClock:\t" << maxCoreClock << std::endl;
	std::cout << "(uint64_t)\tminCoreClock:\t" << minCoreClock << std::endl;
	std::cout << "(bool)\t\tminCoreClock:\t" << can64bits << std::endl;
	/*Test printing End*/
	return (0);
}