/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:25:10 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/04 17:43:28 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <pthread.h>

typedef struct s_const
{
	int			n_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			n_eat;
	long long	start_time;
}	t_const;

typedef struct s_philo
{
	const t_const	*constants;
	int				id;
	long long		to_die;
	long long		to_eat;
	long long		to_sleep;
	int				times_eaten;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		thread;
}	t_philo;

typedef struct	s_gen
{
	t_const			constants;
	// pthread_mutex_t	*fork;
	// pthread_t		*threads;
	t_philo			*philo;
	int				err_code;
}	t_gen;

int	parse_input(int argc, char **argv, t_gen *gen);
int	init_thread(t_gen *gen);

#endif