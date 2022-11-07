/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:33:12 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/07 15:46:10 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>

long long	get_timestamp(void)
{
	struct timeval	time;
	long long		ret;

	if (gettimeofday(&time, NULL))
		return (-1);
	ret = (long long)time.tv_sec * 1000;
	ret += (long long)time.tv_usec / 1000;
	return (ret);
}

void	ft_sleep(int ms)
{
	long long	timestamp;
	long long	goal;

	timestamp = get_timestamp();
	goal = timestamp + ms;
	while (timestamp < goal)
	{
		usleep (100);
		timestamp++;
	}
}