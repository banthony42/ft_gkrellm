/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:04:09 by banthony          #+#    #+#             */
/*   Updated: 2018/01/19 17:04:09 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// clang++ -std=c++98 -Wall -Wextra -Werror ./*.cpp

#include <iostream>
#include <unistd.h>
#include <sys/utsname.h>

#include <sys/sysctl.h>

#include <ctime>
#include <time.h>
#include <mach/mach_types.h>
#include <mach/mach_host.h>
#include <fstream>

#define HOST_NAME_MAX 256      //sensé etre definit dans #include <limits.h>
#define LOGIN_NAME_MAX 256     //senś etre definit dans #include <limits.h>


void host_user_module()
{
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];

    try
    {
        if (gethostname(hostname, HOST_NAME_MAX) < 0)
            throw std::exception();
        if (getlogin_r(username, LOGIN_NAME_MAX) != 0) // existe aussi getlogin() qui renvoi une chaine alloué, surement plus pratique d'ailleurs
            throw std::exception();
    }
    catch (std::exception const &e)
    {
        std::cout << "HOST_USER_ERROR:" << e.what() << std::endl;
    }


    std::cout << "HOSTNAME: " << hostname << std::endl;
    std::cout << "USERNAME: " << username << std::endl;
}

void OS_info_module()
{
    struct utsname sys;

    try
    {
        if (uname(&sys) < 0)
            throw std::exception();
        std::cout << "OS: " << sys.sysname << std::endl;
        std::cout << "nodename: " << sys.nodename << std::endl;
        std::cout << "release: " << sys.release << std::endl;
        std::cout << "version: " << sys.version << std::endl;
        std::cout << "machine: " << sys.machine << std::endl;
    }
    catch (std::exception const &e)
    {
        std::cout << "OS_INFO_ERROR:" << e.what() << std::endl;
    }
}

void date_time_module()
{
    char date[128];
    char timebuf[128];
    time_t temps;
    struct tm timeval;

    // On récupère la date et l'heure actuelles.
    time(&temps);
    timeval = *localtime(&temps);

    // On remplit la chaîne avec le format choisi, puis on l'affiche.
    strftime(date, 128, "%a %x", &timeval);
    strftime(timebuf, 128, "%X %Z", &timeval);

    std::cout << "DATE: " << date << std::endl;
    std::cout << "TIME: " << timebuf << std::endl;
}

//CPU module (Model, clock speed, number of cores, activity, ...)
void cpu_info_module()
{
    uint64_t freq = 0;
    size_t size = sizeof(freq);

    try
    {
        if (sysctlbyname("hw.cpufrequency", &freq, &size, 0, 0) < 0)
            throw std::exception();
    }
    catch (std::exception const &e)
    {
        std::cout << "CPU_INFO_ERROR:" << e.what() << std::endl;
    }
    std::cout << "CPU_FREQU: " << freq << std::endl;
}

void ram_info_module()
{
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;

    //TOUTE LES VALEURS SERONT DANS:
    vm_statistics64_data_t vmstat;

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
        if(KERN_SUCCESS != host_statistics64(mach_host_self(), HOST_VM_INFO64, (host_info64_t)&vmstat, &count))
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

    std::cout << "//Valeurs Brut:\\\\" <<std::endl;
    std::cout << "TOTAL_RAM: " << memsize << std::endl;
    std::cout << "wired : " << wired << std::endl;          //The number of pages that are wired in memory and cannot be paged out.
    std::cout << "active : " << active << std::endl;        //The total number of pages currently in use and pageable.
    std::cout << "inactive : " << inactive << std::endl;    //The number of inactive pages.
    std::cout << "free : " << free << std::endl;            //The total number of free pages in the system.

    std::cout << "//Valeurs similaire a top:\\\\" <<std::endl;
    std::cout << "TOTAL_RAM: " << mem_size << "M" << std::endl;
    std::cout << "PhysMem: " << mem_used << "M used";
    std::cout << " ("  << mem_wired << "M wired), ";
    std::cout << mem_unused << "M unused." << std::endl;
}

void ram_info_module2()
{
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;

    //TOUTE LES VALEURS SERONT DANS:
    vm_statistics64_data_t vmstat;
    uint64_t memsize;
    uint64_t swapusage;

    //POUR CALCUL
    natural_t phys_mem;
    natural_t mem_used;
    natural_t mem_virtual;
    natural_t app_memory;


    size_t size = sizeof(uint64_t);
    vm_size_t pagesize;
    host_page_size(mach_host_self(), &pagesize);
    try
    {
        if (sysctlbyname("hw.memsize", &memsize, &size, 0, 0) < 0)
            throw std::exception();

        if (sysctlbyname("vm.swapusage", &swapusage, &size, 0, 0) < 0)
            throw std::exception();

        if(KERN_SUCCESS != host_statistics64(mach_host_self(), HOST_VM_INFO64, (host_info64_t)&vmstat, &count))
            throw std::exception();

        //CALCUL
        phys_mem = memsize / (1024 * 1024);
        mem_used = (memsize - (vmstat.free_count * pagesize)) / (1024 * 1024);
        mem_virtual = phys_mem + (vmstat.total_uncompressed_pages_in_compressor * pagesize);
    }
    catch (std::exception const &e)
    {
        std::cout << "ERROR_RAM_INFO:" << e.what() << std::endl;
    }


}

int main(void)
{
    std::cout << "-----------USER-HOST------------- " <<std::endl;
    host_user_module();
    std::cout << std::endl;

    std::cout << "-----------OS_INFO--------------- " <<std::endl;
    OS_info_module();
    std::cout << std::endl;

    std::cout << "-----------DATE_TIME------------- " <<std::endl;
    date_time_module();
    std::cout << std::endl;

    std::cout << "-----------CPU_INFO-------------- " <<std::endl;
    cpu_info_module();
    std::cout << std::endl;

    std::cout << "-----------RAM-INFO-------------- " <<std::endl;
    ram_info_module();
    std::cout << std::endl;

    std::cout << "-----------RAM-INFO2-------------- " <<std::endl;
    ram_info_module2();
}