/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:47:41 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/04 14:50:14 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "error.h"
#include "utilities.h"

int	error_glossary(int code)
{
	static const char	*errors[] = {ERR_1, ERR_2, ERR_3, ERR_4, ERR_5};

	if (code <= 0)
		return (0);
	write (2, errors[code - 1], nu_strlen(errors[code - 1]));
	return (code);
}