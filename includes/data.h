/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:25:10 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/07 18:40:31 by khatlas          ###   ########.fr       */
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

typedef struct s_philo
{
	const t_const	*constants;
	bool			dead;
	int				id;
	int				index;
	long long		to_die;
	long long		to_eat;
	long long		to_sleep;
	int				times_eaten;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*death;
	pthread_t		thread;
}	t_philo;

typedef struct	s_gen
{
	t_const			constants;
	pthread_mutex_t	death;
	t_philo			*philo;
	int				err_code;
}	t_gen;

int	parse_input(int argc, char **argv, t_gen *gen);
int	init_thread(t_gen *gen);

#endif