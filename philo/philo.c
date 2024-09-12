/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akay <akay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:18:22 by akay              #+#    #+#             */
/*   Updated: 2024/08/28 19:12:07 by akay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if (ft_timestamp() - philo->last_meal > philo->table->time_to_die
		&& philo->table->someone_died == 0)
	{
		philo->table->someone_died = 1;
		pthread_mutex_unlock(&philo->table->check_dead);
		ft_print(philo->table, ft_timestamp() - philo->table->start_time,
			philo->id, "died");
		return (1);
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	return (0);
}

int	ft_meals_check(t_philo *philo)
{
	int	all_philos_ate;
	int	i;

	pthread_mutex_lock(&philo->table->meals);
	all_philos_ate = 1;
	i = 0;
	while (i < philo->table->num_philo)
	{
		if (philo->table->philos[i]->meal_count <= philo->table->must_eat
			|| philo->table->must_eat == -1)
		{
			all_philos_ate = 0;
			break ;
		}
		i++;
	}
	if (all_philos_ate && !philo->table->max_meals_eaten)
	{
		philo->table->max_meals_eaten = 1;
		pthread_mutex_unlock(&philo->table->meals);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->meals);
	return (0);
}

void	*ft_supervise(void *args)
{
	t_table	*table;
	int		i;
	int		fin;

	table = (t_table *)args;
	i = 0;
	fin = 0;
	while (fin == 0 && table->philos[i])
	{
		fin = table->someone_died + table->max_meals_eaten;
		pthread_mutex_lock(&table->fin);
		table->finished = fin;
		pthread_mutex_unlock(&table->fin);
		ft_death_check(table->philos[i]);
		ft_meals_check(table->philos[i]);
		i++;
		if (i == table->num_philo)
			i = 0;
	}
	return (NULL);
}

static int	check_fin(t_table *table)
{
	int	fin;

	fin = 0;
	pthread_mutex_lock(&table->fin);
	fin = table->finished;
	pthread_mutex_unlock(&table->fin);
	return (fin);
}

void	*ft_live(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (check_fin(philo->table) == 0)
	{
		ft_eat(philo);
		if (check_fin(philo->table))
			break ;
		ft_sleep(philo);
		if (check_fin(philo->table))
			break ;
		ft_think(philo);
	}
	return (NULL);
}
