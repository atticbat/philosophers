/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:44:42 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/09 11:46:38 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

#include <stdbool.h>
#include <stddef.h>

int		nu_strlen(const char *str);
int		nu_atoi(const char *str);
char    *nu_itoa(int n);
size_t  nu_abs(int n);
bool	is_str_numeric(const char *str);

#endif