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
    uint64_t memsize = 0;
    size_t size = sizeof(memsize);

    mach_msg_type_number_t count = sizeof(vm_statistics_data_t) / sizeof(integer_t);//HOST_VM_INFO_COUNT;
    vm_statistics_data_t vmstat;

    double wired = 0;
    double active = 0;
    double inactive = 0;
    double free = 0;

    double percentage = 0;
    natural_t mem_unused;
    natural_t mem_used;
    natural_t mem_wired;

    vm_size_t pagesize;
    host_page_size(mach_host_self(), &pagesize);
    try
    {
        if (sysctlbyname("hw.memsize", &memsize, &size, 0, 0) < 0)
            throw std::exception();
        if(KERN_SUCCESS != host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count))
            throw std::exception();

        // BRUT
        wired = vmstat.wire_count;
        active = vmstat.active_count;
        inactive = vmstat.inactive_count;
        free = vmstat.free_count;

        //CALCUL
        percentage = active / (free + active) * 100.0;
        mem_used = ((vmstat.active_count + vmstat.inactive_count + vmstat.wire_count) * pagesize) / (1024 * 1024);

        mem_unused = (vmstat.free_count * pagesize)  / (1024*1024);
        mem_wired = static_cast<int>((wired * pagesize)/ (1024*1024));

    }
    catch (std::exception const &e)
    {
        std::cout << "ERROR_RAM_INFO:" << e.what() << std::endl;
    }

    std::cout << "--------VALEUR BRUT------------ " <<std::endl;
    std::cout << "TOTAL_RAM: " << memsize << std::endl;
    std::cout << "wired : " << wired << std::endl;          //The number of pages that are wired in memory and cannot be paged out.
    std::cout << "active : " << active << std::endl;        //The total number of pages currently in use and pageable.
    std::cout << "inactive : " << inactive << std::endl;    //The number of inactive pages.
    std::cout << "free : " << free << std::endl;            //The total number of free pages in the system.

    std::cout << "--------CALCUL------------ " <<std::endl;
    std::cout << "percentage: " << percentage << std::endl;
    std::cout << "wired : " << mem_wired << "M" << std::endl; //calcul OK similaire a top (wired)
    std::cout << "unused : " << mem_unused << "M" << std::endl; // calcul OK similaire a valeur de top (memoire unused)
    std::cout << "used : " << mem_used<< "M" << std::endl; // pas tout a fait exact


}

int main(void)
{

    host_user_module();
    std::cout << std::endl;

    OS_info_module();
    std::cout << std::endl;

    date_time_module();
    std::cout << std::endl;

    cpu_info_module();
    std::cout << std::endl;

    ram_info_module();
}