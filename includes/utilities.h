/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:44:42 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/04 14:59:33 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

#include <stdbool.h>

int		nu_strlen(const char *str);
int		nu_atoi(const char *str);
bool	is_str_numeric(const char *str);

#endif