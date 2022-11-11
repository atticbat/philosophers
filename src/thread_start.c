/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:20 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/11 21:21:56 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "time.h"
#include <stdio.h>

void	*thread_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	philo->index = 0;
	pthread_mutex_lock(&philo->shared->begin_m);
	pthread_mutex_unlock(&philo->shared->begin_m);
	philo->to_die = get_timestamp() + philo->constants->time_die;
	while (1)
	{
		long long	timestamp = get_timestamp();
		// philo->index++;
		if (timestamp > philo->to_die)
		{
			pthread_mutex_lock(&philo->shared->death_m);
			if (!philo->shared->death)
			{
				philo->shared->death = true;
				printf("ms: %lld\tphilo %d has died.", philo->to_die, philo->id);
			}
			pthread_mutex_unlock(&philo->shared->death_m);
			break ;
		}
	}
	return (NULL);
}