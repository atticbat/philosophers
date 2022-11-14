/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:20 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/14 18:06:20 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "time.h"
#include <stdio.h>
#include <stdbool.h>

bool	check_death(t_philo *philo)
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
		ft_sleep(25);
	}
	while (1)
	{
		if (check_death(philo))
			break ;

		if (get_timestamp() >= philo->to_die)
		{
			pthread_mutex_lock(&philo->shared->death_m);
			if (!philo->shared->death)
			{
				philo->shared->death = true;
				printf("%lld %d died\n", get_timestamp() - philo->constants->start_time, philo->id);
			}
			pthread_mutex_unlock(&philo->shared->death_m);
			break ;
		}
		else if (philo->constants->n_eat != -1 && philo->times_eaten >= philo->constants->n_eat)
			break ;

		if (check_death(philo))
			break ;

		pthread_mutex_lock(philo->left_fork);
		if (check_death(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		printf("%lld %d has taken a fork\n", get_timestamp()- philo->constants->start_time, philo->id);

		pthread_mutex_lock(&philo->right_fork);
		if (check_death(philo))
		{
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		printf("%lld %d has taken a fork\n", get_timestamp()- philo->constants->start_time, philo->id);

		printf("%lld %d is eating\n", get_timestamp()- philo->constants->start_time, philo->id);
		philo->to_die = get_timestamp() + philo->constants->time_die;
		philo->times_eaten++;

		if (check_death(philo))
		{
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}

		ft_sleep(philo->constants->time_eat);

		if (check_death(philo))
		{
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		pthread_mutex_unlock(&philo->right_fork);
		
		if (check_death(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}

		pthread_mutex_unlock(philo->left_fork);

		if (check_death(philo))
			break ;

		printf("%lld %d is sleeping\n", get_timestamp()- philo->constants->start_time, philo->id);
		ft_sleep(philo->constants->time_sleep);
		
		pthread_mutex_lock(&philo->shared->death_m);
		if (!philo->shared->death)
			printf("%lld %d is thinking\n", get_timestamp()- philo->constants->start_time, philo->id);
		pthread_mutex_unlock(&philo->shared->death_m);
	}
	return (NULL);
}