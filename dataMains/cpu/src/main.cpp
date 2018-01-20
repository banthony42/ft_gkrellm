/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:33:29 by mgras             #+#    #+#             */
/*   Updated: 2018/01/20 11:21:46 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/sysctl.h>
#include <iostream>

//cpu Activity Start
#include <sys/sysctl.h>
#include <sys/types.h>
#include <mach/mach_host.h>
#include <stdlib.h>
//cpu Activity End

int		main(void)
{
	/*Important Start*/
	uint64_t	cpuFrequency	= -1;
	int			nbCores			= -1;
	int			activeCores		= -1;
	uint32_t	cpuType			= -1;
	size_t		cpuUsed;
	size_t		totalCpu;
	size_t		cpuAvailable;
	char		cpuModel[100];
	/*CPU Activity Start*/
	natural_t						cpuCount;
	processor_cpu_load_info_t		cpuInfo;
	mach_msg_type_number_t			nbInfo;
	size_t							system = 0;
	size_t							user = 0;
	size_t							idle = 0;
	size_t							totalSystemTime = 0;
	size_t							totalUserTime = 0;
	size_t							totalIdleTime = 0;
	kern_return_t					r = host_processor_info(mach_host_self(), PROCESSOR_CPU_LOAD_INFO, &cpuCount, reinterpret_cast<processor_info_array_t *>(&cpuInfo), &nbInfo);
	/*CPU Activity Stop*/
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
	size_t sizeCpuModel		= sizeof(char) * 100;
	//La taille des données stockées dans le pointeur seront dans leurs sizes respectives
	/*Utility pointers*/
	//int	i = 0;

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
	if (sysctlbyname("hw.model", &cpuModel, &sizeCpuModel, NULL, 0) < 0)
		std::cout << "cpuModel fail" << std::endl;
	/*Syscalls End*/

	/*CPU activity Syscall Start*/
	if (r != KERN_SUCCESS)
		return (0);
	for (natural_t i = 0; i < cpuCount; i++)
	{
		system = cpuInfo[i].cpu_ticks[CPU_STATE_SYSTEM];
		user = cpuInfo[i].cpu_ticks[CPU_STATE_USER] + cpuInfo[i].cpu_ticks[CPU_STATE_NICE];
		idle = cpuInfo[i].cpu_ticks[CPU_STATE_IDLE];
		totalSystemTime += system;
		totalUserTime += user;
		totalIdleTime += idle;
	}
	totalCpu = totalIdleTime + totalSystemTime + totalUserTime;
	cpuAvailable = totalSystemTime + totalUserTime;
	cpuUsed = totalCpu - cpuAvailable;
	/*CPU activity Syscall End*/

	/*Test printing Start*/
	std::cout << "(uint64_t)\tcpuFrequency:\t\t" << cpuFrequency << std::endl;
	std::cout << "(int)\t\tnbCores:\t\t" << nbCores << std::endl;
	std::cout << "(int)\t\tactiveCores:\t\t" << activeCores << std::endl;
	std::cout << "(uint34_t)\tcpuType:\t\t" << cpuType << std::endl;

	std::cout << "(int)\t\tcpuFamily:\t\t" << cpuFamily << std::endl;
	std::cout << "(uint64_t)\tmaxCoreClock:\t\t" << maxCoreClock << std::endl;
	std::cout << "(uint64_t)\tminCoreClock:\t\t" << minCoreClock << std::endl;
	std::cout << "(bool)\t\tminCoreClock:\t\t" << can64bits << std::endl;
	std::cout << "(char*)\t\tcpuModel:\t\t" << cpuModel << std::endl;

	std::cout << "(size_t)\tCpuTotal:\t\t" << totalCpu << std::endl;
	std::cout << "(size_t)\tCpuWork:\t\t" << cpuAvailable << std::endl;
	//pour avoir le couUsage a chaque tick
	//((nouvelle valueur de cpuAvailable - ancienne valuer de cpu available) / (nouvelle valeur de totalCpu - ancienne valeur de totalCpu)) * 100
	// == Pourcentage du CPU en utilisation

	/*Test printing End*/
	return (0);
}