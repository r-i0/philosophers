/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:48 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/06 12:44:14 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_dining(t_info *info)
{
	int		i;
	t_philo	*p;

	p = info->philo;
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&p[i].thread, NULL, philo_routine, &p[i]) != 0)
			return (-1);
		if (pthread_create(&p[i].death_thread, NULL, observer, &p[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

// void end(void)__attribute__((destructor));

// void end(void)
// {
// 	system("leaks philo");
// }

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (ft_puterror("invalid argument\n"));
	if (philo_init(argv, &info))
		return (ft_puterror("error: init\n"));
	if (start_dining(&info) == -1)
		return (ft_puterror("error: pthread_create\n"));
	if (join_threads(&info) == -1)
		return (ft_puterror("error: pthread_join\n"));
	if (free_info(&info) == -1)
		return (ft_puterror("error: pthread_destroy\n"));
	return (0);
}
