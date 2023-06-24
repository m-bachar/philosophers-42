/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:36:39 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/24 12:03:46 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isint(char *str)
{
	char	*str1;
	char	*str2;
	int		nbr;

	str2 = str;
	nbr = ft_atoi(str);
	if (*str2 == '+')
		str2++;
	str1 = ft_itoa(nbr);
	if (nbr < INT_MIN
		|| nbr > INT_MAX || !ft_strcmp(str1, str2))
		return (free(str1), 0);
	return (free(str1), 1);
}

int	ft_isnumber(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		while (str[j][i])
		{
			if ((str[j][i] >= '0' && str[j][i] <= '9')
				|| (str[j][i] == '-') || (str[j][i] == '+'))
				i++;
			else
				return (0);
		}
		i = 0;
		j++;
	}
	return (1);
}

int	ft_isempty(char **str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 1;
	count = 0;
	while (str[j])
	{
		if (ft_strlen(str[j]) == 0)
			return (0);
		while (str[j][i])
		{
			if (str[j][i] == ' ' || str[j][i] == '\t')
				count++;
			i++;
		}
		if (count == ft_strlen(str[j]))
			return (0);
		i = 0;
		count = 0;
		j++;
	}
	return (1);
}

int	args_values(char **args)
{
	if (ft_atoi(args[1]) > 0 && ft_atoi(args[1]) < 200
		&& ft_atoi(args[2]) >= 60 && ft_atoi(args[3]) >= 60
		&& ft_atoi(args[4]) >= 60)
		return (1);
	return (0);
}

int	parsing(char **args)
{
	int	i;

	i = 1;
	if (!ft_isempty(args) || ft_isnumber(args) || !args_values(args))
		return (0);
	while (args[i])
	{
		if (!ft_isint(args[i]))
			return (0);
		i++;
	}
	return (1);
}
