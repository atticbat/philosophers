/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:04:25 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/04 19:00:43 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static void	*thread_start(void *data)
{
	t_philo	*philo;
	char	*uargv;

	philo = (t_philo *) data;
	(void) philo;
	uargv = malloc (sizeof(char) *2);
	uargv[0] = 'a';
	uargv[1] = '\0';
	return (uargv);
}

int	main(int argc, char **argv)
{
	t_gen	gen;

	if (argc != 5 && argc != 6)
		return (error_glossary(USAGE));
	if (parse_input(argc, argv, &gen))
		return (gen.err_code);
	gen.constants.start_time = get_timestamp();
	if (gen.constants.start_time == -1)
		return (error_glossary(TIMESTAMP_FAIL));
	init_thread(&gen);
	//even threads eat
	// int	i = 0;
	// while (i < gen.constants.n_philo)
	// {
	// 	if ((i + 1) % 2 == 0)
	// 		printf("Eating: philo %d\n", i + 1);
	// 	else
	// 	{
	// 		printf("Sleeping: philo %d\n", i + 1);
	// 	}
	// 	i++;
	// }
	t_philo	philo;
	int	i = 0;

	// while (i < gen.constants.n_philo)
	// {
		philo = gen.philo[i];
		// usleep(50);
		pthread_create(&philo.thread, NULL, &thread_start, &philo);
		// i++;
	// }
	//odd threads sleep
	void	*res = NULL;
	i = 0;

	// while (i < gen.constants.n_philo)
	// {
		// philo = gen.philo[i];
		pthread_join(philo.thread, &res);
		char	*buff = (char *) res;
		printf("res: %s\n", buff);
		free (res);
		// i++;
	// }
//	printf("n_eat: %d, n_philo: %d, time_die: %d, time_eat: %d, time_sleep: %d, time: %lld\n",
//			gen.constants.n_eat, gen.constants.n_philo, gen.constants.time_die,
//			gen.constants.time_eat, gen.constants.time_sleep, gen.constants.start_time);
	return (0);
}