/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:36:40 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/24 12:05:54 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (!create_threads(&dawdaw))
		{
			pthread_mutex_unlock(&dawdaw.philo->death);
			pthread_mutex_destroy(&dawdaw.philo->death);
			pthread_mutex_destroy(&dawdaw.philo->fork);
			pthread_mutex_destroy(&dawdaw.philo->print);
			return (1);
		}
		
	}
	else
	{
		printf("Errors : Arguments count is invalid !\n");
		return (0);
	}
}
