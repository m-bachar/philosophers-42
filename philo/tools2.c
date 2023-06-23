/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 23:37:47 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/12 23:39:39 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strdup(char *s1)
{
	size_t		len;
	char		*dst;

	len = ft_strlen(s1);
	dst = malloc(len * sizeof(char) + 1);
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	ft_memcpy(dst, s1, len);
	return (dst);
}

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = (char *)dst;
	str2 = (char *)src;
	i = 0;
	if (str1 == str2)
		return (dst);
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dst);
}

static	int	number_len(int nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr != '\0')
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*itoa;
	int		j;

	if (!n)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = number_len(n);
	j = 0;
	itoa = malloc((i) * sizeof(char) + 1);
	if (!itoa)
		return (NULL);
	if (n < 0)
	{
		itoa[j++] = '-';
		n *= -1;
	}
	itoa[i] = '\0';
	while (i-- > j)
	{
		itoa[i] = (n % 10) + 48;
		n /= 10;
	}
	return (itoa);
}
