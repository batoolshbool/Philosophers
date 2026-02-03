/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:18:47 by bshbool           #+#    #+#             */
/*   Updated: 2026/02/03 17:14:42 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int is_valid_input(char **argv)
{
	
	//nb_philo(argv[1]): unsigned int
	//die_time(argv[2]): unsigned long
	//eat_time(argv[3]): unsigned long
    //sleep_time(argv[4]): unsigned long
	//must_eat(optional - argv[5]): int
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		//exit_error("Wrong number of arguments"); -> utils file
	if (!is_valid_input(argv))
		////exit_error("Invalid arguments"); -> utils file
	//init_philo(argv, &table); TODO
	//process; TODO
	//clean/free TODO
	return (0);
}