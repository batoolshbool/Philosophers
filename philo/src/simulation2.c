/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:11:28 by bshbool           #+#    #+#             */
/*   Updated: 2026/04/25 14:17:29 by bshbool          ###   ########.fr       */
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
		printf("%lu %d %s\n",
			get_time() - philo->table->start_time,
			philo->id,
			msg);
	pthread_mutex_unlock(&philo->table->print);
}

void	philo_action(t_philo *philo)
{
	if (take_forks(philo))
		return ;
	eat_sleep_think(philo);
}

void	*philo_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->state);
	philo->last_meal_ts = get_time();
	pthread_mutex_unlock(&philo->table->state);
	if (philo->id % 2 == 0)
		usleep(1000);
	else
		usleep(500);
	while (!is_finished(philo->table))
	{
		philo_action(philo);
		if (philo->id % 2)
			usleep(1000);
	}
	return (NULL);
}
