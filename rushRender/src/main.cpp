/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 17:51:08 by banthony          #+#    #+#             */
/*   Updated: 2018/01/21 18:04:34 by jrouthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include "Window.hpp"
#include "Renderer.hpp"
#include "AGraphical.hpp"
#include "NCURSESGraphical.hpp"
#include "../include/NCURSESGraphical.hpp"

/*
void display(AModule *elemt)
{
	std::cout << "Module:\t\t" << elemt->getName() << "\t\tPosition:\t" << elemt->getPosition() << std::endl;
}

for_each(listModule.begin(), listModule.end(), display);
*/

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	try
	{
		AGraphical *graph;
		if (argc > 1 && argv[1][0] == 'n')
		{
			NCURSESGraphical *ncurse = new NCURSESGraphical();
			while (ncurse->isOpen() == true)
			{
				ncurse->updateVisual();
				ncurse->refreshVisual();
			}
			ncurse->close();
			return (0);
		}
		else
			graph = new Renderer();
		while (graph->isOpen())
		{
			graph->updateVisual();
			graph->refreshVisual();
		}
		delete graph;
	}
	catch (std::exception const & e)
	{
		std::cout << "CATCH IN MAIN:" << e.what() << std::endl;
	}

	return (0);
}
