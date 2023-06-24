/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:39:24 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/24 13:13:02 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_list(t_list *lst, char **args)
{
	lst->philos_count = ft_atoi(args[1]);
	lst->time_to_die = ft_atoi(args[2]);
	lst->time_to_eat = ft_atoi(args[3]);
	lst->time_to_sleep = ft_atoi(args[4]);
	if (pthread_mutex_init(&lst->print, NULL) == -1)
	{
		printf("Print Mutex Error!\n");
		return ;
	}
	if (pthread_mutex_init(&lst->death, NULL) == -1)
	{
		printf("Death Mutex Error!\n");
		return ;
	}
	if (!args[5])
		lst->eating_count = -1;
	else
		lst->eating_count = ft_atoi(args[5]);
}

void	print_activity(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->list->print);
	printf("%zu\t%d\t%s\n",
		currenttime() - philo->list->the_begining_of_the_existence,
		philo->id, str);
	if (philo->flag == 1)
		pthread_mutex_unlock(&philo->list->print);
}

void	*philo_stat(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	if (philos->id % 2 == 0)
		usleep(100);
	while (philos->flag)
	{
		pthread_mutex_lock(&philos->fork);
		print_activity(philos, "has taken a fork");
		pthread_mutex_lock(&philos->next->fork);
		print_activity(philos, "has taken a fork");
		print_activity(philos, "is eating");
		pthread_mutex_lock(&philos->list->death);
		philos->lastmeal_time = currenttime();
		philos->eat_counter++;
		pthread_mutex_unlock(&philos->list->death);
		daddysleep(philos->list->time_to_eat);
		pthread_mutex_unlock(&philos->fork);
		pthread_mutex_unlock(&philos->next->fork);
		print_activity(philos, "is sleeping");
		daddysleep(philos->list->time_to_sleep);
		print_activity(philos, "is thinking");
	}
	return (NULL);
}

int	create_threads_2(t_list *shared)
{
	while (shared->philo->flag)
	{
		pthread_mutex_lock(&shared->death);
		if (shared->philo->eat_counter > shared->eating_count
			&& shared->eating_count != -1)
		{
			shared->philo->flag = 0;
			return (0);
		}
		if (currenttime() - shared->philo->lastmeal_time
			> (size_t)shared->time_to_die)
		{
			print_activity(shared->philo, "died");
			shared->philo->flag = 0;
			return (0);
		}
		pthread_mutex_unlock(&shared->death);
		shared->philo = shared->philo->next;
	}
	return (1);
}

int	create_threads(t_list *shared)
{
	int	philos;

	philos = 0;
	shared->the_begining_of_the_existence = currenttime();
	while (philos < shared->philos_count)
	{
		shared->philo->lastmeal_time = currenttime();
		if (pthread_create(&shared->philo->philo,
				NULL, &philo_stat, shared->philo) != 0)
			return (printf("Error while creating threads\n"), 0);
		if (pthread_detach(shared->philo->philo) != 0)
			return (printf("Error while detaching\n"), 0);
		shared->philo = shared->philo->next;
		philos++;
	}
	if (!create_threads_2(shared))
		return (0);
	return (1);
}
