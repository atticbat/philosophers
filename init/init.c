/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:18:34 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/04 14:59:07 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "utilities.h"
#include "error.h"

bool	are_args_numeric(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_str_numeric(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

int	parse_input(int argc, char **argv, t_gen *gen)
{
	gen->err_code = 0;
	if (!are_args_numeric(argc, argv))
	{
		gen->err_code = NON_NUM;
		return (error_glossary(NON_NUM));
	}
	gen->n_eat = nu_atoi(argv[1]);
	gen->n_philo = nu_atoi(argv[2]);
	gen->time_die = nu_atoi(argv[3]);
	gen->time_eat = nu_atoi(argv[4]);
	if (argc == 6)
		gen->time_sleep = nu_atoi(argv[5]);
	else
		gen->time_sleep = -1;
	return (0);
}