/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:20 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/17 23:32:27 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "time.h"
#include "thread_start.h"
#include <stdio.h>
#include <stdbool.h>

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

void	death_in_sleep(t_philo *philo, long long buffer, bool normal)
{
	if (normal)
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
	ft_sleep(buffer);
	death(philo);
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
	long long	buffer = philo->to_die - get_timestamp(); 
	if (buffer < philo->constants->time_eat)
	{
		death_in_sleep(philo, buffer, false);
		return (true);
	}
	ft_sleep(philo->constants->time_eat);
	philo->to_die = get_timestamp() + philo->constants->time_die;
	philo->times_eaten++;
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
	long long	buffer = philo->to_die - get_timestamp(); 
	if (buffer < philo->constants->time_eat)
	{
		death_in_sleep(philo, buffer, true);
		return (true);
	}
	ft_sleep(philo->constants->time_eat);
	philo->to_die = get_timestamp() + philo->constants->time_die;
	philo->times_eaten++;
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
	{
		if (print_message(philo, THINK))
			return (NULL) ;
		ft_sleep(25);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->shared->death_m);
		if (philo->shared->death)
		{
			pthread_mutex_unlock(&philo->shared->death_m);
			break ;
		}
		pthread_mutex_unlock(&philo->shared->death_m);
		if (get_timestamp() >= philo->to_die)
		{
			death(philo);
			break ;
		}
		else if (philo->constants->n_eat != -1 && philo->times_eaten == philo->constants->n_eat)
		{
			pthread_mutex_lock(&philo->shared->eaten_m);
			philo->shared->eaten++;
			if (philo->shared->eaten == philo->constants->n_philo)
			{
				pthread_mutex_unlock(&philo->shared->eaten_m);
				break ;
			}
			pthread_mutex_unlock(&philo->shared->eaten_m);
		}
		else if (philo->constants->n_eat != -1) 
		{
			pthread_mutex_lock(&philo->shared->eaten_m);
			if (philo->shared->eaten == philo->constants->n_philo)
			{
				pthread_mutex_unlock(&philo->shared->eaten_m);
				break ;
			}
			pthread_mutex_unlock(&philo->shared->eaten_m);
		}
		if (philo->id == philo->constants->n_philo - 1)
		{
			if (take_forks_last(philo))
				break ;
		}
		else if (take_forks_normal(philo))
			break ;
		if (print_message(philo, SLEEP))
			break ;
		long long	buffer = philo->to_die - get_timestamp();
		if (buffer <= philo->constants->time_sleep)
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