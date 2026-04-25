/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:06:24 by bshbool           #+#    #+#             */
/*   Updated: 2026/04/25 14:17:39 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// static int	take_forks(t_philo *philo)
// {
// 	pthread_mutex_t	*first;
// 	pthread_mutex_t	*second;

// 	if (philo->id % 2 == 0)
// 	{
// 		first = philo->right_fork;
// 		second = philo->left_fork;
// 	}
// 	else
// 	{
// 		first = philo->left_fork;
// 		second = philo->right_fork;
// 	}
// 	pthread_mutex_lock(first);
// 	print_status(philo, "has taken a fork");
// 	if (is_finished(philo->table))
// 	{
// 		pthread_mutex_unlock(first);
// 		return (1);
// 	}
// 	pthread_mutex_lock(second);
// 	print_status(philo, "has taken a fork");
// 	if (is_finished(philo->table))
// 	{
// 		pthread_mutex_unlock(first);
// 		pthread_mutex_unlock(second);
// 		return (1);
// 	}
// 	return (0);
// }

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
	usleep(philo->table->sleep_time * 1000);
	print_status(philo, "is thinking");
}
