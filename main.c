/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:04:25 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/02 14:11:31 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct	s_gen
{
	int	n_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	n_eat;
}	t_gen;


int	main(int argc, char **argv)
{
	t_gen	gen;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: './philo [number_of_philosophers] [time_to_die] "
			"[time_to_eat] [time_to_sleep] "
			"<number_of_times_each_philosopher_must_eat>'"
			",[] being mandatory and <> being optional.\n");
		return (1);
	}
	gen.n_eat = atoi(argv[1]);
	gen.n_philo = atoi(argv[2]);
	gen.time_die = atoi(argv[3]);
	gen.time_eat = atoi(argv[4]);
	if (argc == 6)
		gen.time_sleep = atoi(argv[5]);
	else
		gen.time_sleep = -1;
	printf("n_eat: %d, n_philo: %d, time_die: %d, time_eat: %d, time_sleep: %d\n",
			gen.n_eat, gen.n_philo, gen.time_die, gen.time_eat, gen.time_sleep);
	return (0);
}