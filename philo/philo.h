/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:07:17 by bshbool           #+#    #+#             */
/*   Updated: 2026/04/25 14:16:39 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_thread_op
{
	THREAD_CREATE,
	THREAD_JOIN
}						t_thread_op;

typedef struct s_philo	t_philo;

typedef struct s_table
{
	unsigned int		nb_philo;
	unsigned long		die_time;
	unsigned long		eat_time;
	unsigned long		sleep_time;
	unsigned long		start_time;
	int					must_eat;
	int					died_end;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		state;
	pthread_t			monitor;
	t_philo				*philos;
}						t_table;

struct					s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		meals;
	unsigned long		last_meal_ts;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
};

/* utils */
void					exit_error(char *msg);
int						ft_isdigit(char c);
long					ft_atol(const char *str);
unsigned long			get_time(void);

/* parsing */
int						is_valid_input(char *str);

/* init */
void					init_table(char **argv, t_table *table);
void					init_mutexes(t_table *table);
void					init_philos(t_table *table);

/* routine */
int						is_finished(t_table *table);
void					print_status(t_philo *philo, char *msg);
void					philo_action(t_philo *philo);
void					*philo_thread(void *data);
void					*monitor_routine(void *data);
void					eat_sleep_think(t_philo *philo);
int						take_forks(t_philo *philo);

/* process */
void					one_philo(t_table *table);
void					thread_control(pthread_t *thread,
							void *(*routine)(void *), void *arg,
							t_thread_op op);
void					process_philo(t_table *table);
void					precise_sleep(unsigned long time, t_table *table);

/* cleanup */
void					cleanup_philo(t_table *table);

#endif
