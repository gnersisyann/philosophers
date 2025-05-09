/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:22 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/09 17:34:23 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	int_len(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	write_number_to_str(char *str, int number, int start)
{
	int	len;
	int	i;

	len = int_len(number);
	i = len - 1;
	while (i >= 0)
	{
		str[start + i] = '0' + (number % 10);
		number /= 10;
		i--;
	}
	str[start + len] = '\0';
}

char	*strjoin_int(const char *prefix, int number)
{
	int		prefix_len;
	int		num_len;
	char	*result;
	int		i;

	prefix_len = 0;
	i = 0;
	while (prefix[prefix_len])
		prefix_len++;
	num_len = int_len(number);
	result = malloc(prefix_len + num_len + 1);
	if (!result)
		return (NULL);
	while (i < prefix_len)
	{
		result[i] = prefix[i];
		i++;
	}
	write_number_to_str(result, number, prefix_len);
	return (result);
}
