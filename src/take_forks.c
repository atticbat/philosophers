/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:54:00 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/20 01:45:32 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "time.h"
#include "thread_start.h"
#include <stdbool.h>

static bool	take_first_fork(t_philo *philo, bool normal)
{
	if (normal)
	{
		pthread_mutex_lock(philo->left_fork);
		if (print_message(philo, FORK))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (true);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		if (print_message(philo, FORK))
		{
			pthread_mutex_unlock(&philo->right_fork);
			return (true);
		}
	}
	return (false);
}

static bool	take_second_fork(t_philo *philo, bool normal)
{
	if (normal)
	{
		pthread_mutex_lock(&philo->right_fork);
		if (print_message(philo, FORK))
		{
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (true);
		}
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (print_message(philo, FORK))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
			return (true);
		}
	}
	return (false);
}

static bool	check_dead_while_eating(t_philo *philo, bool normal)
{
	long long	buffer;

	buffer = philo->to_die - get_timestamp();
	if (buffer < philo->constants->time_eat)
	{
		death_in_sleep(philo, buffer, normal);
		return (true);
	}	
	return (false);
}

static bool	eat(t_philo *philo, bool normal)
{
	if (print_message(philo, EAT))
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
		return (true);
	}
	if (check_dead_while_eating(philo, normal))
		return (true);
	ft_sleep(philo->constants->time_eat);
	philo->to_die = get_timestamp() + philo->constants->time_die;
	philo->times_eaten++;
	return (false);
}

bool	take_forks(t_philo *philo, bool normal)
{
	take_first_fork(philo, normal);
	take_second_fork(philo, normal);
	eat(philo, normal);
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
	return (false);
}
