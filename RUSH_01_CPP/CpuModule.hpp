/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CpuModule.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:01:52 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 14:32:10 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_MODULE
# define CPU_MODULE

# include "AModule.hpp"

class CpuModule : public AModule {
	private:
		uint64_t			_cpuFrequency;
		int					_nbCores;
		int					_activeCores;
		uint32_t			_cpuType;
		size_t				_cpuUsed;
		size_t				_totalCpu;
		size_t				_cpuAvailable;
		uint64_t			_l3CacheSize;
		uint64_t			_l2CacheSize;
		uint64_t			_l1dCacheSize;
		uint64_t			_l1iCacheSize;
		char				*_cpuModel;
		char				*_cpuName;
		timeval				_bootTime;
		size_t				_totalSystem;
		size_t				_totalUser;
		size_t				_totalIdle;
		uint64_t			_maxCoreClock;
		uint64_t			_minCoreClock;

	public:
		CpuModule(void);
		CpuModule(CpuModule const &src);
		CpuModule(bool isActive, int ID, std::string name, int position, int len);
		virtual ~CpuModule(void);

		virtual void		updateSysInfo(void);
		virtual DataStruct	const getData(unsigned int n) const;

		uint64_t			getCpuFrequency(void)	const;
		int					getNbCores(void)		const;
		int					getActiveCores(void)	const;
		uint32_t			getCpuType(void)		const;
		size_t				getCpuUsed(void)		const;
		size_t				getTotalCpu(void)		const;
		size_t				getCpuAvailable(void)	const;
		uint64_t			getL3CacheSize(void)	const;
		uint64_t			getL2CacheSize(void)	const;
		uint64_t			getL1dCacheSize(void)	const;
		uint64_t			getL1iCacheSize(void)	const;
		char				*getCpuModel(void)		const;
		char				*getCpuName(void)		const;
		timeval				getBootTime(void)		const;
		size_t				getTotalSystem(void)	const;
		size_t				getTotalUser(void)		const;
		size_t				getTotalIdle(void)		const;
		uint64_t			getMaxCoreClock(void)	const;
		uint64_t			getMinCoreClock(void)	const;

		void				setCpuFrequency(uint64_t cpuFrequency);
		void				setNbCores(int nbCores);
		void				setActiveCores(int activeCores);
		void				setCpuType(uint32_t cpuType);
		void				setCpuUsed(size_t cpuUsed);
		void				setTotalCpu(size_t totalCpu);
		void				setCpuAvailable(size_t cpuAvailable);
		void				setL3CacheSize(uint64_t l3CacheSize);
		void				setL2CacheSize(uint64_t l2CacheSize);
		void				setL1dCacheSize(uint64_t l1dCacheSize);
		void				setL1iCacheSize(uint64_t l1iCacheSize);
		void				setCpuModel(char *cpuModel);
		void				setCpuName(char *cpuName);
		void				setBootTime(timeval bootTime);
		void				setTotalSystem(size_t totalSystem);
		void				setTotalUser(size_t totalUser);
		void				setTotalIdle(size_t totalIdle);
		void				setMaxCoreClock(uint64_t maxCoreClock);
		void				setMinCoreClock(uint64_t minCoreClock);
};

#endif