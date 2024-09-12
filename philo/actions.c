/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akay <akay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:15:36 by akay              #+#    #+#             */
/*   Updated: 2024/08/26 16:56:24 by akay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->rfork);
		ft_print(philo->table, ft_timestamp() - philo->table->start_time,
			philo->id, "has taken a fork");
		pthread_mutex_lock(philo->lfork);
		ft_print(philo->table, ft_timestamp() - philo->table->start_time,
			philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->lfork);
		ft_print(philo->table, ft_timestamp() - philo->table->start_time,
			philo->id, "has taken a fork");
		pthread_mutex_lock(philo->rfork);
		ft_print(philo->table, ft_timestamp() - philo->table->start_time,
			philo->id, "has taken a fork");
	}
}

void	ft_leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	ft_eat(t_philo *philo)
{
	ft_take_forks(philo);
	pthread_mutex_lock(&philo->table->check_dead);
	philo->last_meal = ft_timestamp();
	pthread_mutex_unlock(&philo->table->check_dead);
	pthread_mutex_lock(&philo->table->meals);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->table->meals);
	ft_print(philo->table, philo->last_meal - philo->table->start_time,
		philo->id, "is eating");
	ft_msleep(philo->table->time_to_eat);
	ft_leave_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo->table, ft_timestamp() - philo->table->start_time,
		philo->id, "is sleeping");
	ft_msleep(philo->table->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_print(philo->table, ft_timestamp() - philo->table->start_time,
		philo->id, "is thinking");
}
