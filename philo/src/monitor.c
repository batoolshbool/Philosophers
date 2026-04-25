/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:06:37 by bshbool           #+#    #+#             */
/*   Updated: 2026/04/25 14:23:18 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	precise_sleep(unsigned long time, t_table *table)
{
	unsigned long	start;

	start = get_time();
	while (!is_finished(table))
	{
		if (get_time() - start >= time)
			break ;
		usleep(500);
	}
}

static int	check_death(t_table *table, int i)
{
	int	died;

	pthread_mutex_lock(&table->state);
	died = 0;
	if (get_time() - table->philos[i].last_meal_ts > table->die_time)
	{
		table->died_end = 1;
		died = 1;
	}
	pthread_mutex_unlock(&table->state);
	if (died)
	{
		pthread_mutex_lock(&table->print);
		printf("%lu %d died\n",
			get_time() - table->start_time,
			table->philos[i].id);
		pthread_mutex_unlock(&table->print);
	}
	return (died);
}

static int	check_meals(t_table *table, unsigned int finished)
{
	int	stop;

	stop = 0;
	if (table->must_eat != -1 && finished == table->nb_philo)
	{
		pthread_mutex_lock(&table->state);
		table->died_end = 1;
		pthread_mutex_unlock(&table->state);
		stop = 1;
	}
	return (stop);
}

void	*monitor_routine(void *data)
{
	t_table				*table;
	unsigned int		i;
	unsigned int		finished;

	table = (t_table *)data;
	while (!is_finished(table))
	{
		i = 0;
		finished = 0;
		while (i < table->nb_philo)
		{
			if (check_death(table, i))
				return (NULL);
			pthread_mutex_lock(&table->state);
			if (table->must_eat != -1
				&& table->philos[i].meals >= (unsigned int)table->must_eat)
				finished++;
			pthread_mutex_unlock(&table->state);
			i++;
		}
		if (check_meals(table, finished))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
