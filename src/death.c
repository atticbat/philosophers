/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 00:18:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/20 01:39:11 by khatlas          ###   ########.fr       */
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
	action_glossary(mode, get_timestamp() - philo->constants->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->shared->death_m);
	return (false);
}

bool	death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->death_m);
	if (philo->shared->death)
	{
		pthread_mutex_unlock(&philo->shared->death_m);
		return (true);
	}
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
