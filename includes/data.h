/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:25:10 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/20 00:50:04 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <stddef.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_const
{
	int			n_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			n_eat;
	long long	start_time;
}	t_const;

typedef struct s_shared
{
	pthread_mutex_t	begin_m;
	pthread_mutex_t	death_m;
	bool			death;
	pthread_mutex_t	eaten_m;
	int				eaten;
}	t_shared;

typedef struct s_philo
{
	const t_const	*constants;
	t_shared		*shared;
	int				id;
	long long		to_die;
	int				times_eaten;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		thread;
}	t_philo;

typedef struct s_gen
{
	t_shared	shared;
	t_const		constants;
	t_philo		*philo;
	int			err_code;
}	t_gen;

int	parse_input(int argc, char **argv, t_gen *gen);
int	init_thread(t_gen *gen);

#endif