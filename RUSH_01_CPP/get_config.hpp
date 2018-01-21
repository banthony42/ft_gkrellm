/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 17:41:37 by banthony          #+#    #+#             */
/*   Updated: 2018/01/21 17:41:37 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_CONFIG_HPP
#define GET_CONFIG_HPP

#include <string>
#include "AModule.hpp"

std::vector<std::string>	 * default_config();
std::vector<std::string> const *get_config();
int	init_list(std::vector<std::string> const &config, std::list<AModule*> *listModule);

#endif //RUSH_01_CPP_GET_CONFIG_HPP
