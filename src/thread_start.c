/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:20 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/07 18:50:04 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include <stdlib.h>
#include "time.h"
#include <stdio.h>

void	*thread_start(void *data)
{
	t_philo	*philo;
	char	*uargv;

	philo = (t_philo *) data;
	philo->index = 0;
	while (!philo->dead)
	{
		philo->index++;
		printf("this happens\n");
		pthread_mutex_lock(philo->death);
		if (philo->index > 5)
			philo->dead = true;
		pthread_mutex_unlock(philo->death);
		printf("philo id: %d, index: %d\n", philo->id, philo->index);
	}
	uargv = malloc (sizeof(char) *2);
	uargv[0] = '0' + philo->id;
	uargv[1] = '\0';
	return (uargv);
}