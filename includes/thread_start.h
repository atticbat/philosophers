/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:55 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/20 00:46:51 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_START_H
# define THREAD_START_H
# define ACT_1 "died"
# define ACT_2 "has taken a fork"
# define ACT_3 "is eating"
# define ACT_4 "is sleeping"
# define ACT_5 "is thinking"

# include "data.h"

typedef enum e_actions
{
	DIE = 1,
	FORK = 2,
	EAT = 3,
	SLEEP = 4,
	THINK = 5
}	t_actions;

void	*thread_start(void *data);
int		action_glossary(int code, long long timestamp, int philo);
bool	take_forks(t_philo *philo, bool normal);
bool	print_message(t_philo *philo, int mode);
void	death(t_philo *philo);
void	death_in_sleep(t_philo *philo, long long buffer, bool normal);
bool	death_check(t_philo *philo);
bool	others_check(t_philo *philo);

#endif