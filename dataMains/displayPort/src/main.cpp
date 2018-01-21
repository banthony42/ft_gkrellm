/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 13:04:22 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 13:35:26 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ApplicationServices/ApplicationServices.h>

int		main(void)
{
	uint32_t	maxDisplays = 50;
	uint32_t	displayId = 0;
	uint32_t	displayCount = 0;

	CGGetActiveDisplayList(maxDisplays, &displayId, &displayCount);
	std::cout << "(uint32_t)\t\tDis play Id\t\t" << displayId << std::endl;
	std::cout << "(bool)\t\t\tDisplay is stereo:\t" << CGDisplayIsStereo(displayId) << std::endl;
	std::cout << "(uint32_t)\t\tModel Nmuber:\t\t" << CGDisplayModelNumber(displayId) << std::endl;
	std::cout << "(int)\t\t\tScreen height:\t\t" << CGDisplayPixelsHigh(displayId) << std::endl;
	std::cout << "(int)\t\t\tScreen width:\t\t" << CGDisplayPixelsWide(displayId) << std::endl;
	std::cout << "(uint32_t)\t\tUnit Number:\t\t" << CGDisplayUnitNumber(displayId) << std::endl;
	std::cout << "(uint32_t)\t\tVendor Number:\t\t" << CGDisplayVendorNumber(displayId) << std::endl;
	return (0);
}