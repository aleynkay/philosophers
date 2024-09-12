/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akay <akay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:15:26 by akay              #+#    #+#             */
/*   Updated: 2024/08/28 15:25:12 by akay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef unsigned long long	t_time;

typedef struct s_table		t_table;

typedef struct s_philo
{
	int						id;
	t_time					last_meal;
	pthread_t				thread;
	pthread_mutex_t			*rfork;
	pthread_mutex_t			*lfork;
	t_table					*table;
	int						meal_count;
}							t_philo;

struct s_table
{
	int				num_philo;
	t_philo			**philos;
	int				must_eat;
	t_time			time_to_die;
	t_time			time_to_eat;
	t_time			time_to_sleep;
	t_time			start_time;
	int				someone_died;
	int				max_meals_eaten;
	int				finished;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meals;
	pthread_mutex_t	fin;
	pthread_t		supervisor;
};

void	table_init(t_table	*table, int ac, char **av);
void	philo_init(t_table *table);
void	create_philos(t_table *table);
void	table_destroy(t_table *table);
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
t_time	ft_timestamp(void);
void	*ft_live(void *args);
void	ft_msleep(t_time time);
void	ft_print(t_table *table, time_t time, int id, char *act);
void	*ft_supervise(void *args);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
int		write_error(char *str);

#endif