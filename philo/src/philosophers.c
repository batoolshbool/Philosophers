/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:18:47 by bshbool           #+#    #+#             */
/*   Updated: 2026/04/25 14:04:38 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_table(char **argv, t_table *table)
{
	table->nb_philo = ft_atol(argv[1]);
	if (table->nb_philo == 0)
		exit_error("Invalid number of philosophers");
	table->die_time = ft_atol(argv[2]);
	table->eat_time = ft_atol(argv[3]);
	table->sleep_time = ft_atol(argv[4]);
	if (argv[5])
		table->must_eat = ft_atol(argv[5]);
	else
		table->must_eat = -1;
	table->died_end = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		exit_error("malloc failed");
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
	{
		free(table->forks);
		exit_error("malloc failed");
	}
}

void	init_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			exit_error("mutex init failed");
		i++;
	}
	if (pthread_mutex_init(&table->print, NULL))
		exit_error("mutex init failed");
	if (pthread_mutex_init(&table->state, NULL))
		exit_error("mutex init failed");
}

void	init_philos(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals = 0;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
		table->philos[i].last_meal_ts = get_time();
		i++;
	}
}

void	cleanup_philo(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->state);
	free(table->forks);
	free(table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (argc != 5 && argc != 6)
		exit_error("Wrong number of arguments");
	i = 1;
	while (i < argc)
	{
		if (!is_valid_input(argv[i]))
			exit_error("Invalid arguments");
		i++;
	}
	init_table(argv, &table);
	init_mutexes(&table);
	init_philos(&table);
	process_philo(&table);
	cleanup_philo(&table);
	return (0);
}
