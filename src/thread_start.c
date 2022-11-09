/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:20 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/09 16:12:22 by khatlas          ###   ########.fr       */
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
	while (!philo->shared->begin)
		ft_sleep(1);
	while (1)
	{
		philo->index++;
		if (philo->index > 5)
		{
			pthread_mutex_lock(&philo->shared->death_m);
			if (!philo->shared->death)
			{
				philo->shared->death = true;
				printf("philo %d has died.", philo->id);
			}
			pthread_mutex_unlock(&philo->shared->death_m);
			break ;
		}
		if (philo->shared->death)
			break ;
	}
	return (NULL);
}