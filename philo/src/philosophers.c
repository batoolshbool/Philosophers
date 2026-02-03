/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshbool <bshbool@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:18:47 by bshbool           #+#    #+#             */
/*   Updated: 2026/02/03 17:22:32 by bshbool          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

	//nb_philo(argv[1]): unsigned int
	//die_time(argv[2]): unsigned long
	//eat_time(argv[3]): unsigned long
    //sleep_time(argv[4]): unsigned long
	//must_eat(optional - argv[5]): int

int is_valid_input(char **argv)
{
	int	i;

	i = 0;
	while(argv[i])
	{
		if(!ft_isdigit(argv[i]))
			return (0);
		else if()
	}
	return (1);
}

/*Each argument:
	contains only digits
	represents a positive integer
Converted values are:
	nb_philo > 0
	die_time > 0
	eat_time > 0
	sleep_time > 0
	must_eat > 0 (if provided)
No signs (+ / -), no spaces, no empty strings.*/

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