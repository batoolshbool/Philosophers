/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:06:24 by bshbool           #+#    #+#             */
/*   Updated: 2026/06/15 20:35:48 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philo *philo)
{
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_slp;
	unsigned long	think_time;

	print_status(philo, "is thinking");
	t_die = philo->table->die_time;
	t_eat = philo->table->eat_time;
	t_slp = philo->table->sleep_time;
	if (t_die > t_eat + t_slp)
		think_time = (t_die - t_eat - t_slp) / 2;
	else
		think_time = 0;
	if (think_time < 1)
		think_time = 1;
	precise_sleep(think_time, philo->table);
}

static void	get_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

static int	lock_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_status(philo, "has taken a fork");
	if (is_finished(philo->table))
	{
		pthread_mutex_unlock(fork);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	get_forks(philo, &first, &second);
	if (lock_fork(philo, first))
		return (1);
	if (lock_fork(philo, second))
	{
		pthread_mutex_unlock(first);
		return (1);
	}
	return (0);
}

void	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->state);
	philo->last_meal_ts = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->table->state);
	print_status(philo, "is eating");
	precise_sleep(philo->table->eat_time, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "is sleeping");
	precise_sleep(philo->table->sleep_time, philo->table);
	think(philo);
}
