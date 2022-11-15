/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:20 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/15 21:14:19 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "time.h"
#include "thread_start.h"
#include <stdio.h>
#include <stdbool.h>

// bool	check_death(t_philo *philo)
// {
// 	if (philo->shared->death)
// 	{
// 		return (true);
// 	}
// 	return (false);
// }

bool	print_message(t_philo *philo, int mode)
{
	pthread_mutex_lock(&philo->shared->death_m);
	if (philo->shared->death)
	{
		pthread_mutex_unlock(&philo->shared->death_m);
		return (true);
	}
	action_glossary(mode, get_timestamp() - philo->constants->start_time, philo->id);
	pthread_mutex_unlock(&philo->shared->death_m);
	return (false);
}

void	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->death_m);
	if (!philo->shared->death)
	{
		philo->shared->death = true;
		printf("%lld %d died\n", get_timestamp()
			- philo->constants->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->shared->death_m);
}

bool	take_forks_last(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	if (print_message(philo, FORK))
	{
		pthread_mutex_unlock(&philo->right_fork);
		return (true);
	}
	pthread_mutex_lock(philo->left_fork);
	if (print_message(philo, FORK))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		return (true);
	}
	if (print_message(philo, EAT))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		return (true);
	}
	long long	buffer = get_timestamp() - philo->to_die;
	if (buffer >= philo->constants->time_eat)
	{
		ft_sleep(buffer);
		death(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		return (true);
	}
	philo->to_die = get_timestamp() + philo->constants->time_die;
	philo->times_eaten++;
	ft_sleep(philo->constants->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (false);
}

bool	take_forks_normal(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_message(philo, FORK))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	pthread_mutex_lock(&philo->right_fork);
	if (print_message(philo, FORK))
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	if (print_message(philo, EAT))
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	long long	buffer = get_timestamp() - philo->to_die;
	if (buffer >= philo->constants->time_eat)
	{
		ft_sleep(buffer);
		death(philo);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	philo->to_die = get_timestamp() + philo->constants->time_die;
	philo->times_eaten++;
	ft_sleep(philo->constants->time_eat);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (false);
}
void	*thread_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	pthread_mutex_lock(&philo->shared->begin_m);
	pthread_mutex_unlock(&philo->shared->begin_m);
	philo->to_die = get_timestamp() + philo->constants->time_die;
	philo->times_eaten = 0;
	if (philo->id % 2 == 0)
		ft_sleep(25);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->death_m);
		if (philo->shared->death)
			break ;
		pthread_mutex_unlock(&philo->shared->death_m);

		if (get_timestamp() >= philo->to_die)
		{
			death(philo);
			break ;
		}
		else if (philo->constants->n_eat != -1 && philo->times_eaten >= philo->constants->n_eat)
			break ;
		if (philo->id == philo->constants->n_philo - 1)
		{
			if (take_forks_last(philo))
				break ;
		}
		else if (take_forks_normal(philo))
			break ;
		if (print_message(philo, SLEEP))
			break ;
		long long	buffer = get_timestamp() - philo->to_die;
		if (buffer >= philo->constants->time_sleep)
		{
			ft_sleep(buffer);
			death(philo);
			break ;
		}
		ft_sleep(philo->constants->time_sleep);
		if (print_message(philo, THINK))
			break ;
	}
	return (NULL);
}