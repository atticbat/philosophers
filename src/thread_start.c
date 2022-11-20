/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:20 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/20 02:09:30 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "time.h"
#include "thread_start.h"
#include <stdio.h>
#include <stdbool.h>

static bool	increment_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->eaten_m);
	philo->shared->eaten++;
	if (philo->shared->eaten == philo->constants->n_philo)
	{
		pthread_mutex_unlock(&philo->shared->eaten_m);
		return (true);
	}
	pthread_mutex_unlock(&philo->shared->eaten_m);
	return (false);
}

bool	others_check(t_philo *philo)
{
	if (get_timestamp() >= philo->to_die)
	{
		death(philo);
		return (true);
	}
	else if (philo->constants->n_eat != -1 && philo->times_eaten
		== philo->constants->n_eat)
	{
		if (increment_eaten(philo))
			return (true);
	}
	else if (philo->constants->n_eat != -1)
	{
		pthread_mutex_lock(&philo->shared->eaten_m);
		if (philo->shared->eaten == philo->constants->n_philo)
		{
			pthread_mutex_unlock(&philo->shared->eaten_m);
			return (true);
		}
		pthread_mutex_unlock(&philo->shared->eaten_m);
	}
	return (false);
}

static bool	go_sleep(t_philo *philo)
{
	long long	buffer;

	if (print_message(philo, SLEEP))
		return (true);
	buffer = philo->to_die - get_timestamp();
	if (buffer <= philo->constants->time_sleep)
	{
		ft_sleep(buffer);
		death(philo);
		return (true);
	}
	ft_sleep(philo->constants->time_sleep);
	return (false);
}

static bool	logic_loop(t_philo *philo)
{
	if (death_check(philo))
		return (true);
	if (others_check(philo))
		return (true);
	if (take_forks(philo, philo->id == philo->constants->n_philo - 1))
		return (true);
	if (print_message(philo, SLEEP))
		return (true);
	if (go_sleep(philo))
		return (true);
	if (print_message(philo, THINK))
		return (true);
	return (false);
}

void	*thread_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	pthread_mutex_lock(&philo->shared->begin_m);
	pthread_mutex_unlock(&philo->shared->begin_m);
	if (philo->constants->n_philo == 1)
	{
		ft_sleep(philo->constants->time_die);
		death(philo);
		return (NULL);
	}
	philo->to_die = get_timestamp() + philo->constants->time_die;
	philo->times_eaten = 0;
	if (philo->id % 2 == 0)
		ft_sleep(philo->constants->time_eat);
	while (!logic_loop(philo))
		;
	return (NULL);
}
