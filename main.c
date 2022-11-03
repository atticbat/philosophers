/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:04:25 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/03 12:26:02 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		ret;

	gettimeofday(&time, NULL);
	ret = (long long)time.tv_sec * 1000;
	ret += (long long)time.tv_usec / 1000;
	return (ret);
}

int	error_glossary(int code)
{
	static const char	*errors[4] = {ERR_1, ERR_2, ERR_3, ERR_4};

	if (code <= 0)
		return (0);
	write (2, errors[code - 1], strlen(errors[code - 1]));
	return (code);
}

bool	is_str_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	are_args_numeric(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_str_numeric(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_gen	gen;

	if (argc != 5 && argc != 6)
		return (error_glossary(USAGE));
	if (!are_args_numeric(argc, argv))
		return (error_glossary(NON_NUM));
	gen.n_eat = atoi(argv[1]);
	gen.n_philo = atoi(argv[2]);
	gen.time_die = atoi(argv[3]);
	gen.time_eat = atoi(argv[4]);
	if (argc == 6)
		gen.time_sleep = atoi(argv[5]);
	else
		gen.time_sleep = -1;
	gen.start_time = get_time();
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