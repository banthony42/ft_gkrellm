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
#include <sstream>
#include <vector>
#include "RamModule.hpp"
#include "OsModule.hpp"
#include "UserModule.hpp"
#include "ClockModule.hpp"
#include "CpuModule.hpp"
#include "NetworkModule.hpp"

/*
 * Prototype gestion modules, et ordre d'affichage au lancement du programme (Minimum requis)
 * BONUS:
 *  Ajout de module en cours d'exec au clic droit sous OPENGL ?
 *  Ajout de module en cours d'exec avec keypad sous ncurse ?
 *
 *  Fichier de config, un module par ligne, l'ordre des modules du fichier correspond a l'ordre dans le prog:
 *  	GRAPHICAL_TYPE
 *      NAME_MODULE
 *      NAME_MODULE
 *      ........... .....
 *  Si aucun fichier de config n'est trouvé:
 *      Creation d'un fichier de config par defaut
 */

/*
void display(AModule *elemt)
{
	std::cout << "Module:\t\t" << elemt->getName() << "\t\tPosition:\t" << elemt->getPosition() << std::endl;
}
 */

std::vector<std::string>	 * default_config()
{
	std::cout << "----CREATING CONFIG FILE----" << std::endl;
	std::vector<std::string> *config = new std::vector<std::string>;
	try
	{
		std::ofstream file;
		file.open("ft_gkrellm.config");
		if (file.is_open())
		{
			file <<	"USER"	<< std::endl;
			file <<	"OS"	<< std::endl;
			file <<	"CLOCK"	<< std::endl;
			file <<	"CPU"	<< std::endl;
			file <<	"RAM"	<< std::endl;
			file <<	"NET"	<< std::endl;

			(*config).push_back("USER");
			(*config).push_back("OS");
			(*config).push_back("CLOCK");
			(*config).push_back("CPU");
			(*config).push_back("RAM");
			(*config).push_back("NET");
			file.close();
		}
		else
			throw std::exception();
	}
	catch (std::exception const &e)
	{
		std::cout << "Error: Creating default config failed" << e.what() << std::endl;
		return (0);
	}
	return (config);
}

std::vector<std::string> const *get_config()
{
	std::cout << "----OPENNING CONFIG FILE----" << std::endl;
	std::vector<std::string> *config = new std::vector<std::string>;
	try
	{
		int i = 0;
		std::string buf;
		std::string tmp;
		std::ifstream file;
		file.open("ft_gkrellm.config", (std::ifstream::in));
		if (file.is_open())
		{
			while (getline(file, buf))
			{
				if (i > 255)
					return config;
				if (!buf.empty())
				{
					std::istringstream flux(buf);
					flux >> tmp;
					(*config).push_back(tmp);
				}
				i++;
			}
			file.close();
		} else
			throw std::exception();
	}
	catch (std::exception const &e)
	{
		std::cout << "Error: Opening config doesn't exist ..." << std::endl;
		config = default_config();
		return (config);
	}
	return (config);
}

bool sortByPosition (AModule *a, AModule *b) {
	if ( a->getPosition() > b->getPosition())
		return (false);
	return (true);
}

bool sortByisActive (AModule *a, AModule *b) {
	if ( a->getIsActive() > b->getIsActive())
		return (true);
	return (false);
}

//MET LES MODULES PRESENT EN ACTIF & SET LA POSITION
int	init_list(std::vector<std::string> const &config, std::list<AModule*> *listModule)
{
	std::vector<std::string>::const_iterator it_config = config.begin();
	std::list<AModule*>::iterator it_list;
	int i = 1;
	bool oneModuleAtLeast = false;

	while (it_config != config.end())
	{
		it_list = (*listModule).begin();
		while (it_list != (*listModule).end())
		{
			if (((*it_config) == (*it_list)->getName()) && (*it_list)->getIsActive() == false)
			{
				(*it_list)->setIsActive(true);
				(*it_list)->setPosition(i);
				oneModuleAtLeast = true;
			}
			it_list++;
		}
		it_config++;
		i++;
	}
	if (oneModuleAtLeast == false)
		return (0);
	listModule->sort(sortByPosition);
	listModule->sort(sortByisActive);
	return (i-1);
}


/*
int main(void)
{
	std::list<AModule*> listModule;
	int nbActiveModule = 0;

	listModule.push_back(new UserModule(false, 0, "USER", 0, 0));
	listModule.push_back(new OsModule(false, 0, "OS", 0, 0));
	listModule.push_back(new ClockModule(false, 0, "CLOCK", 0, 0));
	listModule.push_back(new CpuModule(false, 0, "CPU", 0, 0));
	listModule.push_back(new RamModule(false, 0, "RAM", 0, 0));
	listModule.push_back(new NetworkModule(false, 0, "NET", 0, 0));

	std::vector<std::string> const *config = get_config();

	if ((nbActiveModule = init_list(*config, &listModule)) == 0) {
		std::cout << "No module found" << std::endl;
		return 0;
	}

	//AFFICHAGE DES MODULES ACTIF DANS L'ORDRE VOULUE
	std::cout << "ft_gkrellm.config: there is " << nbActiveModule << " active module:"<< std::endl;
	std::cout << std::endl;

	for_each(listModule.begin(), listModule.end(), display);

	std::cout << std::endl;
	std::cout << "ft_gkrellm.config: end" << std::endl;
	delete config;

	return 0;
}*/