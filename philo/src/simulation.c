/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:06:04 by bshbool           #+#    #+#             */
/*   Updated: 2026/04/25 14:10:26 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	one_philo(t_table *table)
{
	table->start_time = get_time();
	pthread_mutex_lock(&table->print);
	printf("0 1 has taken a fork\n");
	pthread_mutex_unlock(&table->print);
	usleep(table->die_time * 1000);
	pthread_mutex_lock(&table->state);
	table->died_end = 1;
	pthread_mutex_unlock(&table->state);
	pthread_mutex_lock(&table->print);
	printf("%lu 1 died\n", get_time() - table->start_time);
	pthread_mutex_unlock(&table->print);
}

void	thread_control(pthread_t *thread, void *(*routine)(void *), void *arg,
		t_thread_op op)
{
	if (op == THREAD_CREATE)
	{
		if (pthread_create(thread, NULL, routine, arg))
			exit_error("pthread_create failed");
	}
	else if (op == THREAD_JOIN)
	{
		if (pthread_join(*thread, NULL))
			exit_error("pthread_join failed");
	}
}

static void	create_philo_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		thread_control(&table->philos[i].thread, philo_thread,
			&table->philos[i], THREAD_CREATE);
		i++;
	}
}

static void	join_philo_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		thread_control(&table->philos[i].thread, NULL, NULL, THREAD_JOIN);
		i++;
	}
}

void	process_philo(t_table *table)
{
	if (table->must_eat == 0)
		return ;
	if (table->nb_philo == 1)
	{
		one_philo(table);
		return ;
	}
	table->start_time = get_time();
	create_philo_threads(table);
	thread_control(&table->monitor, monitor_routine, table, THREAD_CREATE);
	join_philo_threads(table);
	thread_control(&table->monitor, NULL, NULL, THREAD_JOIN);
}
