/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:48 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 11:44:11 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void end(void)__attribute__((destructor));

// void end(void)
// {
// 	system("leaks philo");
// }

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (ft_puterror("error: invalid argument\n"));
	if (philo_init(argc, argv, &info))
		return (ft_puterror("error: philo_init\n"));
	if (start_dining(&info) == -1)
		return (ft_puterror("error: pthread_create\n"));
	if (join_threads(&info) == -1)
		return (ft_puterror("error: pthread_join\n"));
	if (free_info(&info) == -1)
		return (ft_puterror("error: pthread_destroy\n"));
	return (0);
}
