/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:00:23 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/24 12:44:03 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int content, t_list *dawdaw)
{
	t_philo	*node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->id = content;
	node->next = node;
	node->prev = node;
	node->list = dawdaw;
	node->flag = 1;
	node->eat_counter = 0;
	if (pthread_mutex_init(&node->fork, NULL) == -1)
		return (printf("Fork Mutex Error!\n"), NULL);
	return (node);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;
	t_philo	*first;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	first = *lst;
	while (last->next != *lst)
		last = last->next;
	last->next = new;
	new->next = *lst;
	new->prev = last;
	first->prev = new;
}

int	ft_lstsize(t_philo *lst)
{
	t_philo	*ptr;
	int		i;

	i = 1;
	if (lst == NULL || lst->next == NULL)
		return (0);
	ptr = lst;
	while (ptr->next != lst)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
