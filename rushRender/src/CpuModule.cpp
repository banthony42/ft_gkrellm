/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CpuModule.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:39:13 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 19:32:57 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CpuModule.hpp"

CpuModule::CpuModule(void) : AModule(),
	_cpuFrequency(-1),
	_nbCores(-1),
	_activeCores(-1),
	_cpuType(-1),
	_cpuUsed(-1),
	_totalCpu(-1),
	_cpuAvailable(-1),
	_l3CacheSize(-1),
	_l2CacheSize(-1),
	_l1dCacheSize(-1),
	_l1iCacheSize(-1),
	_cpuModel(NULL),
	_cpuName(NULL)
{
	return ;
}

CpuModule::CpuModule(CpuModule const &src) : AModule(src),
	_cpuFrequency(src.getCpuFrequency()),
	_nbCores(src.getNbCores()),
	_activeCores(src.getActiveCores()),
	_cpuType(src.getCpuType()),
	_cpuUsed(src.getCpuUsed()),
	_totalCpu(src.getTotalCpu()),
	_cpuAvailable(src.getCpuAvailable()),
	_l3CacheSize(src.getL3CacheSize()),
	_l2CacheSize(src.getL2CacheSize()),
	_l1dCacheSize(src.getL1dCacheSize()),
	_l1iCacheSize(src.getL1iCacheSize())
{
	if (src.getCpuModel() != NULL)
	{
		this->_cpuModel = new char[sizeof(src.getCpuModel())];
		strcpy(this->_cpuModel, src.getCpuModel());
	}
	else
		this->_cpuModel = NULL;
	if (src.getCpuName() != NULL)
	{
		this->_cpuName = new char[sizeof(src.getCpuName())];
		strcpy(this->_cpuName, src.getCpuName());
	}
	else
		this->_cpuModel = NULL;
	return ;
}

CpuModule::CpuModule(bool isActive, int ID, std::string name, int position, int len) : AModule(isActive, ID, name, position, len),
	_cpuFrequency(-1),
	_nbCores(-1),
	_activeCores(-1),
	_cpuType(-1),
	_cpuUsed(-1),
	_totalCpu(-1),
	_cpuAvailable(-1),
	_l3CacheSize(-1),
	_l2CacheSize(-1),
	_l1dCacheSize(-1),
	_l1iCacheSize(-1),
	_cpuModel(NULL),
	_cpuName(NULL)
{
	return ;	
}

CpuModule::~CpuModule(void)
{
	if (this->_cpuModel != NULL)
		delete []this->_cpuModel;
	if (this->_cpuName != NULL)
		delete []this->_cpuName;
	return ;
}

void		CpuModule::updateSysInfo(void)
{
	natural_t						cpuCount;
	processor_cpu_load_info_t		cpuInfo;
	mach_msg_type_number_t			nbInfo;
	kern_return_t					r;
	size_t							system = 0;
	size_t							user = 0;
	size_t							idle = 0;
	size_t							sizeCpuFrequency	= sizeof(this->_cpuFrequency);
	size_t							sizeNbCores			= sizeof(this->_nbCores);
	size_t							sizeActiveCores		= sizeof(this->_activeCores);
	size_t							sizeMinCoreClock	= sizeof(this->_minCoreClock);
	size_t							sizeMaxCoreClock	= sizeof(this->_maxCoreClock);
	size_t							sizel1iCacheSize	= sizeof(this->_l1iCacheSize);
	size_t							sizel1dCacheSize	= sizeof(this->_l1dCacheSize);
	size_t							sizel2CacheSize		= sizeof(this->_l2CacheSize);
	size_t							sizel3CacheSize		= sizeof(this->_l3CacheSize);
	size_t							sizeBootTime		= sizeof(this->_bootTime);
	size_t							sizeCpuModel;
	size_t							sizeCpuName;

	r = host_processor_info(mach_host_self(), PROCESSOR_CPU_LOAD_INFO, &cpuCount, reinterpret_cast<processor_info_array_t *>(&cpuInfo), &nbInfo);
	if (sysctlbyname("hw.cpufrequency", &this->_cpuFrequency, &sizeCpuFrequency, NULL, 0) < 0)
		this->_cpuFrequency = -1;
	if (sysctlbyname("hw.ncpu", &this->_nbCores, &sizeNbCores, NULL, 0) < 0)
		this->_nbCores = -1;
	if (sysctlbyname("hw.activecpu", &this->_activeCores, &sizeActiveCores, NULL, 0) < 0)
		this->_activeCores = -1;
	if (sysctlbyname("hw.cpufrequency_max", &this->_maxCoreClock, &sizeMaxCoreClock, NULL, 0) < 0)
		this->_maxCoreClock = -1;
	if (sysctlbyname("hw.cpufrequency_min", &this->_minCoreClock, &sizeMinCoreClock, NULL, 0) < 0)
		this->_minCoreClock = -1;
	sysctlbyname("hw.model", NULL, &sizeCpuModel, NULL, 0);
	if (this->_cpuModel == NULL)
		this->_cpuModel = new char[sizeCpuModel];
	else
	{
		delete [] this->_cpuModel;
		this->_cpuModel = new char[sizeCpuModel];
	}
	sysctlbyname("hw.model", this->_cpuModel, &sizeCpuModel, NULL, 0);
	sysctlbyname("machdep.cpu.brand_string", NULL, &sizeCpuName, NULL, 0);
	if (this->_cpuName == NULL)
		this->_cpuName = new char[sizeCpuName];
	else
	{
		delete [] this->_cpuName;
		this->_cpuName = new char[sizeCpuName];
	}
	sysctlbyname("machdep.cpu.brand_string", this->_cpuName, &sizeCpuName, NULL, 0);
	if (sysctlbyname("hw.l1icachesize", &this->_l1iCacheSize, &sizel1iCacheSize, NULL, 0) < 0)
		this->_l1iCacheSize = -1;
	if (sysctlbyname("hw.l1dcachesize", &this->_l1dCacheSize, &sizel1dCacheSize, NULL, 0) < 0)
		this->_l1dCacheSize = -1;
	if (sysctlbyname("hw.l2cachesize", &this->_l2CacheSize, &sizel2CacheSize, NULL, 0) < 0)
		this->_l2CacheSize = -1;
	if (sysctlbyname("hw.l3cachesize", &this->_l3CacheSize, &sizel3CacheSize, NULL, 0) < 0)
		this->_l3CacheSize = -1;
	if (sysctlbyname("kern.boottime", &this->_bootTime, &sizeBootTime, NULL, 0) < 0)
		this->_l3CacheSize = -1;
	if (r == KERN_SUCCESS)
	{
		for (natural_t i = 0; i < cpuCount; i++)
		{
			system = cpuInfo[i].cpu_ticks[CPU_STATE_SYSTEM];
			user = cpuInfo[i].cpu_ticks[CPU_STATE_USER] + cpuInfo[i].cpu_ticks[CPU_STATE_NICE];
			idle = cpuInfo[i].cpu_ticks[CPU_STATE_IDLE];
			this->_totalSystem += system;
			this->_totalUser += user;
			this->_totalIdle += idle;
		}
		this->_totalCpu = this->_totalIdle + this->_totalSystem + this->_totalUser;
		this->_cpuAvailable = this->_totalSystem + this->_totalUser;
		this->_cpuUsed = this->_totalCpu - this->_cpuAvailable;
	}
	else
	{
		this->_totalSystem = -1;
		this->_totalUser = -1;
		this->_totalIdle = -1;
		this->_totalCpu = -1;
		this->_cpuUsed = -1;
	}
	return ;
}

DataStruct const	CpuModule::getData(unsigned int n) const
{
	DataStruct	dataToReturn;

	if (n == 0)
	{
		uint64_t *ptr = new uint64_t;
		*ptr = this->_cpuFrequency;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(UINT64);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Cpu Frquency");
		return (dataToReturn);
	}
	else if (n == 1)
	{
		int *ptr = new int;
		*ptr = this->_nbCores;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(INT);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Number of Cores");
		return (dataToReturn);
	}
	else if (n == 2)
	{
		int *ptr = new int;
		*ptr = this->_activeCores;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(INT);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Number of Active Cores");
		return (dataToReturn);
	}
	else if (n == 3)
	{
		uint32_t *ptr = new uint32_t;
		*ptr = this->_cpuType;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(UINT32);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Cpu type");
		return (dataToReturn);
	}
	else if (n == 4)
	{
		size_t *ptr = new size_t;
		*ptr = this->_cpuUsed;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(SIZET);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Used Cpu");
		return (dataToReturn);
	}
	else if (n == 5)
	{
		size_t *ptr = new size_t;
		*ptr = this->_totalCpu;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(SIZET);
		dataToReturn.setDisplayType(GRAPH);
		dataToReturn.setVarLabel("Total Cpu");
		return (dataToReturn);
	}
	else if (n == 6)
	{
		size_t *ptr = new size_t;
		*ptr = this->_cpuAvailable;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(SIZET);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Cpu Available");
		return (dataToReturn);
	}
	else if (n == 7)
	{
		uint64_t *ptr = new uint64_t;
		*ptr = this->_l3CacheSize;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(UINT64);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("L3 Cache size");
		return (dataToReturn);
	}
	else if (n == 8)
	{
		uint64_t *ptr = new uint64_t;
		*ptr = this->_l2CacheSize;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(UINT64);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("L2 Cache size");
		return (dataToReturn);
	}
	else if (n == 9)
	{
		uint64_t *ptr = new uint64_t;
		*ptr = this->_l1dCacheSize;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(UINT64);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("L1i Cache size");
		return (dataToReturn);
	}
	else if (n == 10)
	{
		uint64_t *ptr = new uint64_t;
		*ptr = this->_l1iCacheSize;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(UINT64);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("L1d Cache size");
		return (dataToReturn);
	}
	else if (n == 11)
	{
		if (this->_cpuModel == NULL)
			return (dataToReturn);
		char *ptr = new char[std::strlen(this->_cpuModel) * sizeof(char)];
		std::strcpy(ptr, this->_cpuModel);
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(CHAR_PTR);
		dataToReturn.setDisplayType(STRING);
		dataToReturn.setVarLabel("Cpu Model");
		return (dataToReturn);
	}
	else if (n == 12)
	{
		if (this->_cpuName == NULL)
			return (dataToReturn);
		char *ptr = new char[std::strlen(this->_cpuName) * sizeof(char)];
		std::strcpy(ptr, this->_cpuName);
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(CHAR_PTR);
		dataToReturn.setDisplayType(STRING);
		dataToReturn.setVarLabel("Cpu family");
		return (dataToReturn);
	}
	else if (n == 13)
	{
		timeval *ptr = new timeval;
		*ptr = this->_bootTime;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(TIMEVAL);
		dataToReturn.setDisplayType(TIME_VAL);
		dataToReturn.setVarLabel("Boot Time");
		return (dataToReturn);
	}
	else if (n == 14)
	{
		size_t *ptr = new size_t;
		*ptr = this->_totalSystem;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(SIZET);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Total system Cpu Usage");
		return (dataToReturn);
	}
	else if (n == 15)
	{
		size_t *ptr = new size_t;
		*ptr = this->_totalUser;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(SIZET);
		dataToReturn.setDisplayType(GRAPH);
		dataToReturn.setVarLabel("Total user Cpu Usage");
		return (dataToReturn);
	}
	else if (n == 16)
	{
		size_t *ptr = new size_t;
		*ptr = this->_totalIdle;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(SIZET);
		dataToReturn.setDisplayType(GRAPH);
		dataToReturn.setVarLabel("Total iddle Cpu Usage");
		return (dataToReturn);
	}
	else if (n == 17)
	{
		uint64_t *ptr = new uint64_t;
		*ptr = this->_maxCoreClock;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(UINT64);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Maximum Core Clock");
		return (dataToReturn);
	}
	else if (n == 18)
	{
		uint64_t *ptr = new uint64_t;
		*ptr = this->_minCoreClock;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(UINT64);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Minimum Core Clock");
		return (dataToReturn);
	}
	return (dataToReturn);
}

uint64_t	CpuModule::getCpuFrequency(void)	const			{ return (this->_cpuFrequency); }
int			CpuModule::getNbCores(void)			const			{ return (this->_nbCores); }
int			CpuModule::getActiveCores(void)		const			{ return (this->_activeCores); }
uint32_t	CpuModule::getCpuType(void)			const			{ return (this->_cpuType); }
size_t		CpuModule::getCpuUsed(void)			const			{ return (this->_cpuUsed); }
size_t		CpuModule::getTotalCpu(void)		const			{ return (this->_totalCpu); }
size_t		CpuModule::getCpuAvailable(void)	const			{ return (this->_cpuAvailable); }
uint64_t	CpuModule::getL3CacheSize(void)		const			{ return (this->_l3CacheSize); }
uint64_t	CpuModule::getL2CacheSize(void)		const			{ return (this->_l2CacheSize); }
uint64_t	CpuModule::getL1dCacheSize(void)	const			{ return (this->_l1dCacheSize); }
uint64_t	CpuModule::getL1iCacheSize(void)	const			{ return (this->_l1iCacheSize); }
char		*CpuModule::getCpuModel(void)		const			{ return (this->_cpuModel); }
char		*CpuModule::getCpuName(void)		const			{ return (this->_cpuName); }
timeval		CpuModule::getBootTime(void)		const			{ return (this->_bootTime); }

void		CpuModule::setCpuFrequency(uint64_t cpuFrequency)	{ this->_cpuFrequency = cpuFrequency; }
void		CpuModule::setNbCores(int nbCores)					{ this->_nbCores = nbCores; }
void		CpuModule::setActiveCores(int activeCores)			{ this->_activeCores = activeCores; }
void		CpuModule::setCpuType(uint32_t cpuType)				{ this->_cpuType = cpuType; }
void		CpuModule::setCpuUsed(size_t cpuUsed)				{ this->_cpuUsed = cpuUsed; }
void		CpuModule::setTotalCpu(size_t totalCpu)				{ this->_totalCpu = totalCpu; }
void		CpuModule::setCpuAvailable(size_t cpuAvailable)		{ this->_cpuAvailable = cpuAvailable; }
void		CpuModule::setL3CacheSize(uint64_t l3CacheSize)		{ this->_l3CacheSize = l3CacheSize; }
void		CpuModule::setL2CacheSize(uint64_t l2CacheSize)		{ this->_l2CacheSize = l2CacheSize; }
void		CpuModule::setL1dCacheSize(uint64_t l1dCacheSize)	{ this->_l1dCacheSize = l1dCacheSize; }
void		CpuModule::setL1iCacheSize(uint64_t l1iCacheSize)	{ this->_l1iCacheSize = l1iCacheSize; }
void		CpuModule::setCpuModel(char *cpuModel)				{
	if (this->_cpuModel != NULL)
		delete [] this->_cpuModel;
	this->_cpuModel = new char[sizeof(cpuModel)];
	strcpy(this->_cpuModel, cpuModel);
}
void		CpuModule::setCpuName(char *cpuName)				{
	if (this->_cpuName != NULL)
		delete [] this->_cpuName;
	this->_cpuName = new char[sizeof(cpuName)];
	strcpy(this->_cpuName, cpuName);
	return ;
}
void		CpuModule::setBootTime(timeval bootTime)			{ this->_bootTime = bootTime; }
void		CpuModule::setTotalSystem(size_t totalSystem)		{ this->_totalSystem = totalSystem; }
void		CpuModule::setTotalUser(size_t totalUser)			{ this->_totalUser = totalUser; }
void		CpuModule::setTotalIdle(size_t totalIdle)			{ this->_totalIdle = totalIdle; }
void		CpuModule::setMaxCoreClock(uint64_t maxCoreClock)	{ this->_maxCoreClock = maxCoreClock; }
void		CpuModule::setMinCoreClock(uint64_t minCoreClock)	{ this->_minCoreClock = minCoreClock; }

/*int		main(void)
{
	CpuModule	io(true, 0, "aiou", 0, 0);

	io.updateSysInfo();
	std::cout << *(reinterpret_cast<uint64_t*>((io.getData(0)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<int*>((io.getData(1)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<int*>((io.getData(2)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<uint32_t*>((io.getData(3)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<size_t*>((io.getData(4)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<size_t*>((io.getData(5)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<size_t*>((io.getData(6)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<uint64_t*>((io.getData(7)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<uint64_t*>((io.getData(8)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<uint64_t*>((io.getData(9)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<uint64_t*>((io.getData(10)).getDataAddr())) << std::endl;
	std::cout << (reinterpret_cast<char*>((io.getData(11)).getDataAddr())) << std::endl;
	std::cout << (reinterpret_cast<char*>((io.getData(12)).getDataAddr())) << std::endl;
	//std::cout << *(reinterpret_cast<timeval*>((io.getData(13)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<size_t*>((io.getData(14)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<size_t*>((io.getData(15)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<size_t*>((io.getData(16)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<uint64_t*>((io.getData(17)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<uint64_t*>((io.getData(18)).getDataAddr())) << std::endl;
	return (0);
}*/
/*
	const void *tr = dataToReturn.getDataAddr();
	uint64_t test2 = *(reinterpret_cast<uint64_t const *>(tr));
	std::cout << test2 << std::endl;
*/