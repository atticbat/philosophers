/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:25:10 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/04 14:40:48 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <pthread.h>

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
	int				err_code;
}	t_gen;

int	parse_input(int argc, char **argv, t_gen *gen);

#endif