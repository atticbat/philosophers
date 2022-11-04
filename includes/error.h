/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:50:15 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/04 14:19:36 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# define ERR_1 "Usage: './philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] <number_of_times_each_philosopher_must_eat>', \
[] being mandatory and <> being optional.\n"
# define ERR_2 "Argument(s) provided is(are) non-numeric.\n"
# define ERR_3 "Memory allocation failure.\n"
# define ERR_4 "Thread initialisation failure.\n"
# define ERR_5 "Failed to receive timestamp.\n"

typedef enum e_errors
{
	USAGE = 1,
	NON_NUM = 2,
	MEM_ALLOC = 3,
	THREAD_INIT = 4,
	TIMESTAMP_FAIL = 5
}	t_errors;

int	error_glossary(int code);

#endif