/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:36:43 by mbachar           #+#    #+#             */
/*   Updated: 2023/06/24 13:08:43 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				eat_counter;
	size_t			lastmeal_time;
	pthread_t		philo;
	pthread_mutex_t	fork;
	int				flag;
	struct s_philo	*prev;
	struct s_philo	*next;
	struct s_list	*list;
}				t_philo;

typedef struct s_list
{
	int				philos_count;
	size_t			the_begining_of_the_existence;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				eating_count;
	struct s_philo	*philo;
}				t_list;

/*	Tools	*/
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
int			ft_strcmp(char	*s1, char	*s2);
int			ft_strlen(char *str);
char		*ft_strdup(char *s1);
void		*ft_memcpy(void *dst, void *src, size_t n);
void		ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo		*ft_lstnew(int content, t_list *dawdaw);
int			ft_lstsize(t_philo *lst);

/*	Parsing	*/
int			ft_isint(char *str);
int			ft_isnumber(char **str);
int			ft_isempty(char **str);
int			args_values(char **args);
int			parsing(char **args);

/*	Philo	*/
size_t		currenttime(void);
void		daddysleep(size_t timestamp);
void		fill_list(t_list *lst, char **args);
void		print_activity(t_philo *philo, char *str);
void		*philo_stat(void *philo);
int			create_threads(t_list *philo);
int			create_threads_2(t_list *shared);
int			norminette(t_list *dawdaw);

#endif
