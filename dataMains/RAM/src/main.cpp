/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:01:24 by mgras             #+#    #+#             */
/*   Updated: 2018/01/20 14:11:14 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/mach_types.h>
#include <mach/mach_host.h>
#include <sys/sysctl.h>
#include <iostream>

int		main(void)
{
	mach_msg_type_number_t count = sizeof(vm_statistics_data_t) / sizeof(integer_t);//HOST_VM_INFO_COUNT;
	vm_statistics_data_t vmstat;

	//VALEUR BRUT
	uint64_t memsize = 0;
	double wired = 0;
	double active = 0;
	double inactive = 0;
	double free = 0;

	//POUR CALCUL
	natural_t mem_size;
	natural_t mem_unused;
	natural_t mem_used;
	natural_t mem_wired;

	size_t size = sizeof(memsize);
	vm_size_t pagesize;
	host_page_size(mach_host_self(), &pagesize);
	try
	{
		if (sysctlbyname("hw.memsize", &memsize, &size, 0, 0) < 0)
			throw std::exception();
		if(KERN_SUCCESS != host_statistics64(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count))
			throw std::exception();

		// BRUT
		wired = vmstat.wire_count;
		active = vmstat.active_count;
		inactive = vmstat.inactive_count;
		free = vmstat.free_count;

		//CALCUL
		mem_used = (memsize - (free * pagesize)) / (1024 * 1024);//((vmstat.active_count + vmstat.inactive_count + vmstat.wire_count) * pagesize) / (1024 * 1024);
		mem_unused = (vmstat.free_count * pagesize)  / (1024*1024);
		mem_wired = static_cast<int>((wired * pagesize)/ (1024*1024));
		mem_size = memsize / (1024 * 1024);
	}
	catch (std::exception const &e)
	{
		std::cout << "ERROR_RAM_INFO:" << e.what() << std::endl;
	}

	std::cout << "(uint_64_t)\t\tTotal RAM:\t\t" << memsize << std::endl;
	std::cout << "(double)\t\tWired Pages:\t\t" << wired << std::endl;			//The number of pages that are wired in memory and cannot be paged out.
	std::cout << "(double)\t\tActive Pages:\t\t" << active << std::endl;		//The total number of pages currently in use and pageable.
	std::cout << "(double)\t\tInactive Pages:\t\t" << inactive << std::endl;	//The number of inactive pages.
	std::cout << "(double)\t\tFree Pages:\t\t" << free << std::endl;			//The total number of free pages in the system.
	std::cout << std::endl;
	std::cout << "(natural_t)\t\tTotal Memory:\t\t" << mem_size << "(Mbytes)" << std::endl;
	std::cout << "(natural_t)\t\tUsed Memory:\t\t" << mem_used << "(Mbytes)" << std::endl;
	std::cout << "(natural_t)\t\tWired Memory:\t\t" << mem_wired << "(Mbytes)" << std::endl;
	std::cout << "(natural_t)\t\tUnused Memory:\t\t" << mem_unused << "(Mbytes)" << std::endl;
}