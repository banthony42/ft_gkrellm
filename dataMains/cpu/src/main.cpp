/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:33:29 by mgras             #+#    #+#             */
/*   Updated: 2018/01/20 13:18:41 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//sysctl includes start
#include <sys/types.h>
#include <sys/sysctl.h>
//sysctl includes stop

//cpu Activity includes Start
#include <sys/sysctl.h>
#include <sys/types.h>
#include <mach/mach_host.h>
#include <stdlib.h>
//cpu Activity includes End

//Boottime include start
#include <time.h>
//Boottime include End

#include <iostream>

int		main(void)
{
	/*Important Start*/
	uint64_t		cpuFrequency	= -1;
	int				nbCores			= -1;
	int				activeCores		= -1;
	uint32_t		cpuType			= -1;
	size_t			cpuUsed			= -1;
	size_t			totalCpu		= -1;
	size_t			cpuAvailable	= -1;
	uint64_t		physicalMem		= -1;
	uint64_t		l3CacheSize		= -1;
	uint64_t		l2CacheSize		= -1;
	uint64_t		l1dCacheSize	= -1;
	uint64_t		l1iCacheSize	= -1;
	char			cpuModel[100];
	char			cpuName[50];
	struct timeval	boottime;

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
	size_t sizeCan64bits	= sizeof(int);
	size_t sizel1iCacheSize	= sizeof(l1iCacheSize);
	size_t sizel1dCacheSize	= sizeof(l1dCacheSize);
	size_t sizel2CacheSize	= sizeof(l2CacheSize);
	size_t sizel3CacheSize	= sizeof(l3CacheSize);
	size_t sizeCpuType		= sizeof(cpuType);
	size_t sizeCpuModel		= sizeof(char) * 100;
	size_t sizeCpuName		= sizeof(char) * 50;
	size_t sizePhysicalMem	= sizeof(uint64_t);
	size_t sizeBoottime		= sizeof(boottime);
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
	if (sysctlbyname("machdep.cpu.brand_string", &cpuName, &sizeCpuName, NULL, 0) < 0)
		std::cout << "cpuName fail" << std::endl;
	if (sysctlbyname("hw.memsize", &physicalMem, &sizePhysicalMem, NULL, 0) < 0)
		std::cout << "Physical memory" << std::endl;
	if (sysctlbyname("hw.l1icachesize", &l1iCacheSize, &sizel1iCacheSize, NULL, 0) < 0)
		l1iCacheSize = -1;
	if (sysctlbyname("hw.l1dcachesize", &l1dCacheSize, &sizel1dCacheSize, NULL, 0) < 0)
		l1dCacheSize = -1;
	if (sysctlbyname("hw.l2cachesize", &l2CacheSize, &sizel2CacheSize, NULL, 0) < 0)
		l2CacheSize = -1;
	if (sysctlbyname("hw.l3cachesize", &l3CacheSize, &sizel3CacheSize, NULL, 0) < 0)
		l3CacheSize = -1;
	if (sysctlbyname("kern.boottime", &boottime, &sizeBoottime, NULL, 0) < 0)
		l3CacheSize = -1;
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
	std::cout << "---IMPORTANT---" << std::endl;
	std::cout << "(uint64_t)\tcpuFrequency:\t\t" << cpuFrequency << std::endl;
	std::cout << "(int)\t\tnbCores:\t\t" << nbCores << std::endl;
	std::cout << "(int)\t\tactiveCores:\t\t" << activeCores << std::endl;
	std::cout << "(uint34_t)\tcpuType:\t\t" << cpuType << std::endl;
	std::cout << "(char*)\t\tcpuName:\t\t" << cpuName << std::endl;
	std::cout << "(int)\t\tPhysical Memory:\t" << physicalMem << std::endl;
	std::cout << "(char*)\t\tBootTime(epoch):\t" << boottime.tv_sec * 1000 << std::endl;
	std::cout << "(size_t)\tCpuTotal:\t\t" << totalCpu << std::endl;
	std::cout << "(size_t)\tCpuWork:\t\t" << cpuAvailable << std::endl;
	//pour avoir le couUsage a chaque tick
	//((nouvelle valueur de cpuAvailable - ancienne valuer de cpu available) / (nouvelle valeur de totalCpu - ancienne valeur de totalCpu)) * 100
	// == Pourcentage du CPU en utilisation

	std::cout << std::endl << "---BONUS---" << std::endl;
	std::cout << "(int)\t\tcpuFamily:\t\t" << cpuFamily << std::endl;
	std::cout << "(uint64_t)\tmaxCoreClock:\t\t" << maxCoreClock << std::endl;
	std::cout << "(uint64_t)\tminCoreClock:\t\t" << minCoreClock << std::endl;
	std::cout << "(bool)\t\t64bits Support ?:\t" << can64bits << std::endl;
	std::cout << "(char*)\t\tcpuModel:\t\t" << cpuModel << std::endl;
	std::cout << "(uint64_t)\tl1iCacheSize:\t\t" << l1iCacheSize << std::endl;
	std::cout << "(uint64_t)\tl1dCacheSize:\t\t" << l1dCacheSize << std::endl;
	std::cout << "(uint64_t)\tl2CacheSize:\t\t" << l2CacheSize << std::endl;
	std::cout << "(uint64_t)\tl3CacheSize:\t\t" << l3CacheSize << std::endl;

	/*Test printing End*/
	return (0);
}