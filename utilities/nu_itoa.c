/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nu_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:12:07 by khatlas           #+#    #+#             */
/*   Updated: 2022/11/09 11:47:51 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

static size_t	count_digits(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = (n / 10) * -1;
		i += 2;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

size_t	nu_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

static int	fill_string(char *str, int n)
{
	int	i;

	i = 0;
	if (n / 10 != 0)
		i = fill_string(str, n / 10);
	else if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	str[i] = nu_abs(n % 10) + '0';
	i++;
	str[i] = '\0';
	return (i);
}

char	*nu_itoa(int n)
{
	char	*ptr;
	size_t	len;

	len = count_digits(n);
	if (len == 0)
		len = 1;
	ptr = (char *) malloc ((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	fill_string(ptr, n);
	return (ptr);
}
