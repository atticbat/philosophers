/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:04:25 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/14 16:48:34 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "philo.h"
#include "time.h"
#include "error.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
	free (gen.philo);
	// int	i = 0;
	// ft_sleep(10000);
	// while (!gen.philo[i].shared.dead)
	// {
	// 	i++;
	// 	if (i >= gen.constants.n_philo)
	// 		i = 0;
	// }
	// while (!gen.philo[i].dead)
	// {
	// 	ft_sleep(20);
	// 	i++;
	// }
	// i = 0;
	// void	*res = NULL;
	// while (i < gen.constants.n_philo)
	// {
	// 	pthread_join(gen.philo[i].thread, &res);
	// 	if (gen.philo[i].dead)
	// 		printf("res: %s\n", (char *) res);
	// 	if (res)
	// 	{
	// 		free (res);
	// 		res = NULL;
	// 	}
	// 	i++;
	// }
	return (0);
}