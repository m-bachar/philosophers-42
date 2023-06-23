/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:36:40 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/23 01:48:03 by mbachar          ###   ########.fr       */
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
		while (i++ < ft_atoi(av[1]))
			ft_lstadd_back(&dawdaw.philo, ft_lstnew(i, &dawdaw));
		fill_list(&dawdaw, av);
		if (!create_threads(&dawdaw))
		{
			pthread_mutex_lock(&dawdaw.death);
			pthread_mutex_destroy(&dawdaw.death);
			return (1);
		}
		
	}
	else
		return (0);
}
