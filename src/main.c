/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:04:25 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/04 14:37:24 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_gen	gen;

	if (argc != 5 && argc != 6)
		return (error_glossary(USAGE));
	if (parse_input(argc, argv, &gen))
		return (gen.err_code);
	gen.start_time = get_timestamp();
	if (gen.start_time == -1)
		return (error_glossary(TIMESTAMP_FAIL));
	gen.fork = malloc (sizeof (pthread_mutex_t) * gen.n_philo);
	if (!gen.fork)
		return (error_glossary(MEM_ALLOC));
	int	i = 0;
	while (i < gen.n_philo)
	{
		if (pthread_mutex_init(&(gen.fork[i]), NULL) != 0)
			return (error_glossary(THREAD_INIT));
		i++;
	}
	gen.philo = malloc (sizeof(t_philo) * gen.n_philo);
	if (!gen.philo)
	{
		free (gen.fork);
		return (error_glossary(MEM_ALLOC));
	}
	printf("n_eat: %d, n_philo: %d, time_die: %d, time_eat: %d, time_sleep: %d, time: %lld\n",
			gen.n_eat, gen.n_philo, gen.time_die, gen.time_eat, gen.time_sleep, gen.start_time);
	return (0);
}