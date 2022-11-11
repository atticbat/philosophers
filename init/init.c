/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:18:34 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/11 21:22:24 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "utilities.h"
#include "error.h"
#include "thread_start.h"
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

static int	init_philo(t_philo *philo, t_gen *gen, int id)
{
	int	left_fork;

	philo->id = id;
	philo->constants = &gen->constants;
	pthread_mutex_init(&philo->right_fork, NULL);
	left_fork = id - 1;
	if (left_fork < 0)
		left_fork = gen->constants.n_philo + left_fork;
	philo->left_fork = &gen->philo[left_fork].right_fork;
	philo->shared = &gen->shared;
	return (0);
}

int	init_philos(t_gen *gen)
{
	int	i;

	gen->shared.death = false;
	gen->philo = malloc (sizeof(t_philo) * gen->constants.n_philo);
	if (!gen->philo)
	{
		gen->err_code = MEM_ALLOC;
		return (error_glossary(MEM_ALLOC));
	}
	i = 0;
	while (i < gen->constants.n_philo)
	{
		init_philo(&gen->philo[i], gen, i);
		i++;
	}
	pthread_mutex_init(&gen->shared.death_m, NULL);
	pthread_mutex_init(&gen->shared.begin_m, NULL);
	pthread_mutex_lock(&gen->shared.begin_m);
	i = 0;
	while (i < gen->constants.n_philo)
	{
		pthread_create(&gen->philo[i].thread, NULL, &thread_start, &gen->philo[i]);
		i++;
		if (i == gen->constants.n_philo)
			pthread_mutex_unlock(&gen->shared.begin_m);
	}
	i = 0;
	while (i < gen->constants.n_philo)
	{
		pthread_join(gen->philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&gen->shared.death_m);
	pthread_mutex_destroy(&gen->shared.begin_m);
	return (0);
}

int	init_thread(t_gen *gen)
{
	if (init_philos(gen))
		return (gen->err_code);
	return (0);
}