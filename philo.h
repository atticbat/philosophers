/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:13:41 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/03 12:17:40 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

# define ERR_1 "Usage: './philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] <number_of_times_each_philosopher_must_eat>', [] being mandatory and <> being optional.\n"
# define ERR_2 "Argument(s) provided is(are) non-numeric.\n"
# define ERR_3 "Memory allocation failure.\n"
# define ERR_4 "pthread_mutex_init failure.\n"

typedef enum e_errors
{
	USAGE = 1,
	NON_NUM = 2,
	MEM_ALLOC = 3,
	THREAD_INIT = 4
}	t_errors;

typedef struct s_philo
{
	long long	to_die;
	long long	to_eat;
	long long	to_sleep;
	int			left_fork;
	int			right_fork;
}	t_philo;


typedef struct	s_gen
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	long long		start_time;
}	t_gen;

// typedef
// # define ERROR C(USAGE)C(NON_NUMERIC)C(MUTEX_INIT)
// # define C(x) x,
// enum color { ERROR TOP };
// # undef C

// # define C(x) #x
// # define FOREACH_ERROR(ERROR)	\
// 		ERROR(error_usage)		\
// 		ERROR(error_non_numeric)\
// 		ERROR(error_mutex_init)	\
// 		ERROR(error_malloc)		\

// # define GENERATE_ENUM(ENUM) ENUM,
// # define GENERATE_STRING(STRING) #STRING,

// typedef enum e_error
// {
// 	FOREACH_ERROR(GENERATE_ENUM)
// };

#endif