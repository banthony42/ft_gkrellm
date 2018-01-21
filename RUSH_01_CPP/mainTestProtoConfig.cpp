/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTestRam.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 18:14:43 by banthony          #+#    #+#             */
/*   Updated: 2018/01/20 18:14:43 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include "RamModule.hpp"
#include "CpuModule.hpp"
#include "OsModule.hpp"

/*
 * Prototype gestion modules, et ordre d'affichage au lancement du programme (Minimum requis)
 * BONUS:
 *  Ajout de module en cours d'exec au clic droit sous OPENGL ?
 *  Ajout de module en cours d'exec avec keypad sous ncurse ?
 *
 *  Fichier de config, un module par ligne:
 *      NAME_MODULE ORDER
 *      NAME_MODULE ORDER
 *      ........... .....
 *  Si aucun fichier de config n'est trouvé:
 *      Creation d'un fichier de config par defaut
 */

int main(void)
{
    std::string config;
    try
    {
        std::ifstream file;
        std::string file_name = "ft_gkrellm.config";
        file.open(file_name, (std::ifstream::out | std::ifstream::in));
        if (file.is_open())
        {
            while(std::getline(file, config))
                ;
            file.close();
        }
        else
            throw std::exception();
    }
    catch (std::exception const &e)
    {
        std::cout << "Error: Opening config" << e.what() << std::endl;
    }

    std::cout << config << std::endl;











    // TEST DES MODULES
    RamModule ram(true, 0, "RamModule", 0, 0);
    ram.updateSysInfo();

    OsModule os(true, 0, "Os", 0, 0);
    os.updateSysInfo();

    DataStruct data0;
    DataStruct data1;
    DataStruct data2;
    DataStruct data3;
    DataStruct data4;
    DataStruct data5;
    DataStruct data6;
    DataStruct data7;
    DataStruct data8;
    DataStruct data9;
    data0 = ram.getData(0);
    data1 = ram.getData(1);
    data2 = ram.getData(2);
    data3 = ram.getData(3);
    data4 = ram.getData(4);
    data5 = ram.getData(5);
    data6 = ram.getData(6);
    data7 = ram.getData(7);
    data8 = ram.getData(8);
    data9 = ram.getData(9);

    std::cout << "val_0: " << *(reinterpret_cast<uint64_t *>(data0.getDataAddr())) << std::endl;
    std::cout << "val_1: " << *(reinterpret_cast<uint64_t *>(data1.getDataAddr())) << std::endl;
    std::cout << "val_2: " << *(reinterpret_cast<uint64_t *>(data2.getDataAddr())) << std::endl;
    std::cout << "val_3: " << *(reinterpret_cast<double *>(data3.getDataAddr())) << std::endl;
    std::cout << "val_4: " << *(reinterpret_cast<double *>(data4.getDataAddr())) << std::endl;
    std::cout << "val_5: " << *(reinterpret_cast<double *>(data5.getDataAddr())) << std::endl;
    std::cout << "val_6: " << *(reinterpret_cast<double *>(data6.getDataAddr())) << std::endl;
    std::cout << "val_7: " << *(reinterpret_cast<double *>(data7.getDataAddr())) << std::endl;
    std::cout << "val_8: " << *(reinterpret_cast<double *>(data8.getDataAddr())) << std::endl;
    std::cout << "val_9: " << *(reinterpret_cast<uint64_t *>(data9.getDataAddr())) << std::endl;

    DataStruct data10;
    DataStruct data11;
    DataStruct data12;
    DataStruct data13;
    DataStruct data14;
    data10 = os.getData(0);
    data11 = os.getData(1);
    data12 = os.getData(2);
    data13 = os.getData(3);
    data14 = os.getData(4);
    std::cout << "(char*)\t\tOS:\t\t" << reinterpret_cast<char*>(data10.getDataAddr()) << std::endl;
    std::cout << "(char*)\t\tnodename:\t" << reinterpret_cast<char *>(data11.getDataAddr())<< std::endl;
    std::cout << "(char*)\t\trelease:\t" << reinterpret_cast<char *>(data12.getDataAddr())<< std::endl;
    std::cout << "(char*)\t\tversion:\t" << reinterpret_cast<char*>(data13.getDataAddr())<< std::endl;
    std::cout << "(char*)\t\tarch:\t\t" << reinterpret_cast<char*>(data14.getDataAddr())<< std::endl;



    DataStruct data20;
    DataStruct data21;
    data20 = os.getData(0);
    data21 = os.getData(1);
    std::cout << "(char*)\t\tHostname:\t\t" << reinterpret_cast<char*>(data20.getDataAddr()) << std::endl;
    std::cout << "(char*)\t\tUsername:\t\t" << reinterpret_cast<char*>(data21.getDataAddr()) << std::endl;

    return 0;
}
