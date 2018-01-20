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
#include <sys/types.h>
#include <sys/sysctl.h>
#include <iostream>

int		main(void)
{
	mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
	vm_statistics64_data_t vmstat;

	//VALEUR BRUT
	uint64_t memsize;
	xsw_usage swapusage;

	//POUR CALCUL TOP
	uint64_t mem_size;
	uint64_t mem_unused;
	uint64_t mem_used;
	uint64_t mem_wired;

	//POUR CALCUL ACTIVITY MONITOR
	double a_mem_used;
	double a_mem_virtual;
	double a_app_mem;
	double a_file_cache;
	double a_wired_mem;
	double a_compress;

	size_t size = sizeof(memsize);
	size_t size_swap = sizeof(swapusage);
	vm_size_t pagesize;
	host_page_size(mach_host_self(), &pagesize);

	try
	{
		if (sysctlbyname("hw.memsize", &memsize, &size, 0, 0) < 0)
			throw std::exception();

		if (sysctlbyname("vm.swapusage", &swapusage, &size_swap, 0, 0) < 0)
			throw std::exception();

		if(KERN_SUCCESS != host_statistics64(mach_host_self(), HOST_VM_INFO64, (host_info_t)&vmstat, &count))
			throw std::exception();

		//TOP
		mem_used = (memsize - (vmstat.free_count * pagesize)) / (1024 * 1024);//((vmstat.active_count + vmstat.inactive_count + vmstat.wire_count) * pagesize) / (1024 * 1024);
		mem_unused = (vmstat.free_count * pagesize)  / (1024*1024);
		mem_wired = static_cast<int>((vmstat.wire_count * pagesize)/ (1024*1024));
		mem_size = memsize / (1024 * 1024);

		//ACTIVITY MONITOR
		a_mem_virtual = static_cast<double>(memsize + static_cast<double>(vmstat.total_uncompressed_pages_in_compressor * pagesize)) / (1024 * 1024);
		a_app_mem = static_cast<double>(vmstat.internal_page_count * pagesize) / (1024 * 1024);
		a_file_cache= static_cast<double>(vmstat.external_page_count * pagesize) / (1024 * 1024);
		a_wired_mem = static_cast<double>(vmstat.wire_count * pagesize) / (1024 * 1024);
		a_compress = static_cast<double>(vmstat.compressor_page_count * pagesize) / (1024 * 1024);
		a_mem_used = a_app_mem + a_wired_mem + a_compress;
	}
	catch (std::exception const &e)
	{
		std::cout << "ERROR_RAM_INFO:" << e.what() << std::endl;
	}

	std::cout << "--------------------------BRUT----------------------------------------" << std::endl;
	std::cout << "(uint_64_t)\t\t\tTotal RAM:\t\t" << memsize << std::endl;
	std::cout << "(vm_statistics64_data_t)" << std::endl;
	std::cout << "\t\t\t\tWired Pages:\t\t" << vmstat.wire_count << std::endl;			//The number of pages that are wired in memory and cannot be paged out.
	std::cout << "\t\t\t\tActive Pages:\t\t" << vmstat.active_count << std::endl;		//The total number of pages currently in use and pageable.
	std::cout << "\t\t\t\tInactive Pages:\t\t" << vmstat.inactive_count << std::endl;	//The number of inactive pages.
	std::cout << "\t\t\t\tFree Pages:\t\t" << vmstat.free_count << std::endl;			//The total number of free pages in the system.
	std::cout << "\t\t\t\tAnd more ....\t\t" << std::endl;
	std::cout << "(xsw_usage)" << std::endl;
	std::cout << "\t\t\t\tSwap Used:\t\t" << swapusage.xsu_used << std::endl;
	std::cout << "\t\t\t\tSwap Available:\t\t" << swapusage.xsu_avail << std::endl;
	std::cout << "\t\t\t\tSwap Total:\t\t" << swapusage.xsu_total << std::endl;
	std::cout << "\t\t\t\tAnd more ....\t\t" << std::endl;
	std::cout << std::endl;
	std::cout << "-------------------TRAITEMENT-INFO-TOP--------------------------------" << std::endl;
	std::cout << "(uint64_t)\t\tUsed Memory:\t\t" << mem_used << "(Mbytes)\t- Dispo dans cmd top" << std::endl;
	std::cout << "(uint64_t)\t\tWired Memory:\t\t" << mem_wired << "(Mbytes)\t- Dispo dans cmd top" << std::endl;
	std::cout << "(uint64_t)\t\tUnused Memory:\t\t" << mem_unused << "(Mbytes)\t- Dispo dans cmd top" << std::endl;
	std::cout << "-------------------TRAITEMENT-INFO-ACTIVITY-MONITOR--------------------" << std::endl;
	std::cout << "(uint64_t)\t\tPhysical Memory:\t" << mem_size << "(Mbytes)" << std::endl;
	std::cout << "(double)\t\tMemory Used:\t\t" << a_mem_used << "(Mbytes)" << std::endl;
	std::cout << "(double)\t\tCached Files:\t\t" << a_file_cache << "(Mbytes)" << std::endl;
	std::cout << "(double)\t\tSwap Used:\t\t" << static_cast<double>(static_cast<double>(swapusage.xsu_used)  / (1024 * 1024))<< "(Mbytes)" << std::endl;
	std::cout << "(double)\t\tApp Memory:\t\t" << a_app_mem << "(Mbytes)" << std::endl;
	std::cout << "(double)\t\tWired Memory:\t\t" << a_wired_mem << "(Mbytes)" << std::endl;
	std::cout << "(double)\t\tCompressed:\t\t" << a_compress << "(Mbytes)" << std::endl;
	std::cout << "(double)\t\tVirtual Memory:\t\t" << a_mem_virtual << "(Mbytes)" << std::endl;
}