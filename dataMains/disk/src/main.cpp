/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 17:13:22 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 17:21:42 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/statvfs.h>

long GetAvailableSpace(const char* path)
{
	struct statvfs stat;

	if (statvfs(path, &stat) != 0)
		return -1;
	return stat.f_bsize * stat.f_bavail;
}

int		main(void)
{
	std::cout << GetAvailableSpace("/Users/mgras/Desktop") << std::endl;
	return (0);
}