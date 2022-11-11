/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:20 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/11 22:45:40 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "time.h"
#include <stdio.h>

void	*thread_start(void *data)
{
	t_philo	*philo;
	long long	timestamp;

	philo = (t_philo *) data;
	pthread_mutex_lock(&philo->shared->begin_m);
	pthread_mutex_unlock(&philo->shared->begin_m);
	philo->to_die = get_timestamp() + philo->constants->time_die;
	philo->to_eat = get_timestamp() + philo->constants->time_eat;
	philo->to_sleep = get_timestamp() + philo->constants->time_sleep;
	philo->times_eaten = 0;
	while (1)
	{
		timestamp = get_timestamp();
		if (timestamp >= philo->to_die || (philo->constants->n_eat != -1 && philo->times_eaten >= philo->constants->n_eat))
		{
			pthread_mutex_lock(&philo->shared->death_m);
			if (!philo->shared->death)
			{
				philo->shared->death = true;
				printf("ms: %lld\tphilo %d has died.\n", philo->to_die, philo->id);
			}
			pthread_mutex_unlock(&philo->shared->death_m);
			break ;
		}
		else if (timestamp >= philo->to_eat)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->right_fork);
			philo->to_die = timestamp + philo->constants->time_die;
			philo->to_eat = get_timestamp() + philo->constants->time_eat;
			philo->times_eaten++;
			printf("ms: %lld\tphilo %d has eaten.\n", timestamp, philo->id);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
		}
		else if (timestamp >= philo->to_sleep)
		{
			printf("ms: %lld\tphilo %d is sleeping.\n", timestamp, philo->id);
			philo->to_sleep = get_timestamp() + philo->constants->time_sleep;
			ft_sleep(philo->constants->time_sleep);
		}
		else
		{
			printf("ms: %lld\tphilo %d is thinking.\n", timestamp, philo->id);
			ft_sleep((philo->to_sleep - timestamp));
		}
	}
	return (NULL);
}