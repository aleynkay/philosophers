/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akay <akay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:18:01 by akay              #+#    #+#             */
/*   Updated: 2024/08/28 19:51:01 by akay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table	*table, int argc, char **argv)
{
	table->num_philo = ft_atoi(argv[1]);
	table->philos = (t_philo **)malloc(sizeof(t_philo *) * table->num_philo);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->num_philo);
	if (!table->philos || !table->forks)
		return ;
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	pthread_mutex_init(&table->check_dead, NULL);
	pthread_mutex_init(&table->meals, NULL);
	pthread_mutex_init(&table->fin, NULL);
	table->start_time = ft_timestamp();
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->someone_died = 0;
	table->max_meals_eaten = 0;
	table->finished = 0;
	philo_init(table);
}

void	philo_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!table->philos[i])
			return ;
		table->philos[i]->id = i + 1;
		table->philos[i]->last_meal = table->start_time;
		table->philos[i]->lfork = &table->forks[i];
		table->philos[i]->rfork = &table->forks[(i + 1) % table->num_philo];
		table->philos[i]->table = table;
		table->philos[i]->meal_count = 0;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

static void	case_one_philo(t_table *table)
{
	int	fin;

	fin = 0;
	pthread_detach(table->philos[0]->thread);
	while (fin == 0)
	{
		pthread_mutex_lock(&table->fin);
		fin = table->finished;
		pthread_mutex_unlock(&table->fin);
		ft_msleep(100);
	}
	pthread_join(table->supervisor, NULL);
	return ;
}

void	create_philos(t_table *table)
{
	int	i;

	pthread_create(&table->supervisor, NULL, ft_supervise, table);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_create(&table->philos[i]->thread, NULL,
			ft_live, table->philos[i]);
		i++;
	}
	if (table->num_philo == 1)
	{
		case_one_philo(table);
		return ;
	}
	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(table->supervisor, NULL);
}

void	table_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->check_dead);
	pthread_mutex_destroy(&table->meals);
	pthread_mutex_destroy(&table->fin);
	i = 0;
	while (i < table->num_philo)
	{
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
	free(table->forks);
}
