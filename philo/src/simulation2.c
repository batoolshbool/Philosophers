/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:11:28 by bshbool           #+#    #+#             */
/*   Updated: 2026/06/16 16:25:58 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_finished(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->state);
	end = table->died_end;
	pthread_mutex_unlock(&table->state);
	return (end);
}

void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->print);
	if (!is_finished(philo->table))
	{
		printf("%lu %d %s\n",
			get_time() - philo->table->start_time,
			philo->id,
			msg);
	}
	pthread_mutex_unlock(&philo->table->print);
}

// void	*philo_thread(void *data)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)data;
// 	if (philo->id % 2 == 0)
// 		precise_sleep(philo->table->eat_time, philo->table);
// 	while (!is_finished(philo->table))
// 	{
// 		if (!take_forks(philo))
// 			eat_sleep_think(philo);
// 	}
// 	return (NULL);
// }

void	*philo_thread(void *data)
{
	t_philo			*philo;
	unsigned long	delay;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
	{
		delay = philo->table->eat_time;
		if (delay > philo->table->die_time / 2)
			delay = philo->table->die_time / 2;
		precise_sleep(delay, philo->table);
	}
	while (!is_finished(philo->table))
	{
		if (!take_forks(philo))
			eat_sleep_think(philo);
	}
	return (NULL);
}

int	thread_control(pthread_t *thread, void *(*routine)(void *), void *arg,
		t_thread_op op)
{
	if (op == THREAD_CREATE)
	{
		if (pthread_create(thread, NULL, routine, arg))
			return (1);
	}
	else if (op == THREAD_JOIN)
	{
		if (pthread_join(*thread, NULL))
			return (1);
	}
	return (0);
}
