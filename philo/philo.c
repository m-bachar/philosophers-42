/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:36:40 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/24 13:10:14 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	currenttime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	daddysleep(size_t timestamp)
{
	size_t	currently;

	currently = currenttime();
	while (currenttime() < currently + timestamp)
		usleep(100);
}

int	norminette(t_list *dawdaw)
{
	if (!create_threads(dawdaw))
	{
		pthread_mutex_unlock(&dawdaw->death);
		pthread_mutex_destroy(&dawdaw->death);
		pthread_mutex_destroy(&dawdaw->philo->fork);
		pthread_mutex_destroy(&dawdaw->print);
		return (1);
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_list	dawdaw;
	int		i;

	i = 0;
	dawdaw.philo = NULL;
	if (ac == 5 || ac == 6)
	{
		if (!parsing(av))
		{
			printf("Errors : Arguments content is invalid !\n");
			return (0);
		}
		while (i++ < ft_atoi(av[1]))
			ft_lstadd_back(&dawdaw.philo, ft_lstnew(i, &dawdaw));
		fill_list(&dawdaw, av);
		if (norminette(&dawdaw) == 1)
			return (1);
		return (0);
	}
	else
	{
		printf("Errors : Arguments count is invalid !\n");
		return (0);
	}
}
