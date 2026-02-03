/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:07:17 by bshbool           #+#    #+#             */
/*   Updated: 2026/02/03 11:56:59 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
typedef struct s_philo;

typedef struct s_table
{
    unsigned int nb_philo;
    unsigned long die_time;
    unsigned long eat_time;
    unsigned long sleep_time;
	unsigned long start_time;
    int must_eat;
    int died_end;
    pthread_mutex_t *forks;
	s_philo	philos;
} t_table;

typedef struct s_philo
{
	pthread_t	thread;
	unsigned int		id;
	unsigned int		meals;
	unsigned int		since_last_meal;
	pthread_mutex_t*left_fork;
	pthread_mutex_t	*right_fork;
	t_table	*rules;

}	t_philo;


#endif

