/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glossary.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:47:41 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/20 01:47:18 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "error.h"
#include "utilities.h"
#include "thread_start.h"

int	error_glossary(int code)
{
	static const char	*errors[] = {ERR_1, ERR_2, ERR_3, ERR_4, ERR_5};

	if (code <= 0)
		return (0);
	write (2, errors[code - 1], nu_strlen(errors[code - 1]));
	return (code);
}

int	action_glossary(int code, long long timestamp, int philo)
{
	static const char	*actions[] = {ACT_1, ACT_2, ACT_3, ACT_4, ACT_5};

	if (code <= 0)
		return (0);
	printf("%lld %d %s\n", timestamp, philo, actions[code - 1]);
	return (code);
}
