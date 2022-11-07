/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:18:34 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/05 01:02:47 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "utilities.h"
#include "error.h"
#include <stdlib.h>

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
	gen->constants.n_philo = nu_atoi(argv[1]);
	gen->constants.n_eat = nu_atoi(argv[2]);
	gen->constants.time_die = nu_atoi(argv[3]);
	gen->constants.time_eat = nu_atoi(argv[4]);
	if (argc == 6)
		gen->constants.time_sleep = nu_atoi(argv[5]);
	else
		gen->constants.time_sleep = -1;
	return (0);
}

// #include <stdio.h>
static int	init_philo(t_philo *philo, t_gen *gen, int id)
{
	int	left_fork;

	philo->id = id;
	philo->constants = &gen->constants;
	pthread_mutex_init(&philo->right_fork, NULL);
	left_fork = id - 1;
	if (left_fork < 0)
		left_fork = gen->constants.n_philo + left_fork;
	// printf("philo %d\tleft %d\tright %d\n", id, left_fork, id);
	philo->left_fork = &gen->philo[left_fork].right_fork;
	if (id == 0)
		
	return (0);
}

int	init_philos(t_gen *gen)
{
	int	i;

	gen->philo = malloc (sizeof(t_philo) * gen->constants.n_philo);
	if (!gen->philo)
	{
		// free (gen->fork);
		gen->err_code = MEM_ALLOC;
		return (error_glossary(MEM_ALLOC));
	}
	// gen->threads = malloc(sizeof(pthread_t) * gen->constants.n_philo);
	// if (!gen->threads)
	// {
	// 	// free (gen->fork);
	// 	free (gen->philo);
	// 	gen->err_code = MEM_ALLOC;
	// 	return (error_glossary(MEM_ALLOC));
	// }
	i = 0;
	while (i < gen->constants.n_philo)
	{
		init_philo(&gen->philo[i], gen, i);
		i++;
	}
	return (0);
}

int	init_thread(t_gen *gen)
{
	// int	i;

	// gen->fork = malloc (sizeof (pthread_mutex_t) * gen->constants.n_philo);
	// if (!gen->fork)
	// 	return (error_glossary(MEM_ALLOC));
	// i = 0;
	// while (i < gen->constants.n_philo)
	// {
	// 	if (pthread_mutex_init(&(gen->fork[i]), NULL) != 0)
	// 		return (error_glossary(THREAD_INIT));
	// 	i++;
	// }
	if (init_philos(gen))
		return (gen->err_code);
	return (0);
}