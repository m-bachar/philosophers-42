/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:39:24 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/23 01:52:15 by mbachar          ###   ########.fr       */
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

void	fill_list(t_list *lst, char **args)
{
	lst->philo->flag = 1;
	lst->philos_count = ft_atoi(args[1]);
	lst->time_to_die = ft_atoi(args[2]);
	lst->time_to_eat = ft_atoi(args[3]);
	lst->time_to_sleep = ft_atoi(args[4]);
	if (!args[5])
		lst->eating_count = -1;
	else
		lst->eating_count = ft_atoi(args[5]);
	if (pthread_mutex_init(&lst->death, NULL) == -1)
	{
		printf("Death Mutex Error!\n");
		return ;
	}
	if (pthread_mutex_init(&lst->eat, NULL) == -1)
	{
		printf("Eat Mutex Error!\n");
		return ;
	}
}

void	print_activity(t_philo *philo, char *str)
{
	printf("%zu\t%d\t%s\n",currenttime() - philo->list->the_begining_of_the_existence, philo->id, str);
}

void	*philo_stat(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	if (philos->id % 2 == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&philos->fork);
		print_activity(philos, "has taken a fork");
		pthread_mutex_lock(&philos->next->fork);
		print_activity(philos, "has taken a fork");
		print_activity(philos, "is eating");
		philos->lastmeal_time = currenttime();
		philos->eat_counter++;
		daddysleep(philos->list->time_to_eat);
		pthread_mutex_unlock(&philos->fork);
		pthread_mutex_unlock(&philos->next->fork);
		print_activity(philos, "is sleeping");
		daddysleep(philos->list->time_to_sleep);
		print_activity(philos, "is thinking");
	}
	return (NULL);
}

int	create_threads(t_list *shared)
{
	int	philos;

	philos = 0;
	shared->the_begining_of_the_existence = currenttime();
	while (philos < shared->philos_count)
	{
		shared->philo->lastmeal_time = currenttime();
		if (pthread_create(&shared->philo->philo, NULL, &philo_stat, shared->philo) != 0)
			return (printf("Error\n"), 0);
		pthread_detach(shared->philo->philo);
		shared->philo = shared->philo->next;
		philos++;
	}
	while(1)
	{
		if (shared->philo->eat_counter > shared->eating_count && shared->eating_count != -1)
		{
			print_activity(shared->philo, "All philos ate");
			break ;
		}
		if (currenttime() - shared->philo->lastmeal_time > (size_t)shared->time_to_die)
		{
			print_activity(shared->philo, "died");
			break ;
		}
		shared->philo = shared->philo->next;
	}
	return (0);
}