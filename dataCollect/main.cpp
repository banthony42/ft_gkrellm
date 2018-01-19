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
    long page_size = 0;
    uint64_t memsize = 0;
    size_t size = sizeof(memsize);

    try
    {
        if (sysctlbyname("hw.memsize", &memsize, &size, 0, 0) < 0)
            throw std::exception();
        if ((page_size = sysconf(_SC_PAGE_SIZE)) < 0)
            throw std::exception();
    }
    catch (std::exception const &e)
    {
        std::cout << "ERROR_RAM_INFO:" << e.what() << std::endl;
    }
    std::cout << "TOTAL_RAM: " << memsize << std::endl;
    std::cout << "PAGE_SIZE: " << page_size << std::endl;
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