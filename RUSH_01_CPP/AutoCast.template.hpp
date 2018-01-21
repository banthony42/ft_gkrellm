/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoCast.template.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:53:34 by banthony          #+#    #+#             */
/*   Updated: 2018/01/21 14:53:34 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCAST_TEMPLATE_HPP
#define AUTOCAST_TEMPLATE_HPP

#include <string>

template <typename T>
float autoCast(T val) {
	return (static_cast<float>(val));
}

template <typename T>
std::string autoCast(T val) {
	std::string str;
	str = val;
	return (str);
}

/*
template <typename T>
std::string autoCast<char*>(T val) {
	std::string str;
	str = val;
	return (str);
}
*/

#endif //RUSH_01_CPP_AUTOCAST_TEMPLATE_HPP
