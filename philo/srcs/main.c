/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:48 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/09 09:43:12 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rule	rule;

	if (argc < 5 || argc > 6)
		return (ft_puterror("error: invalid argument\n"));
	if (philo_init(argc, argv, &rule))
		return (ft_puterror("error: philo_init\n"));
	if (start_dining(&rule) == -1)
		return (ft_puterror("error: pthread_create\n"));
	if (join_threads(&rule) == -1)
		return (ft_puterror("error: pthread_join\n"));
	if (free_rule(&rule) == -1)
		return (ft_puterror("error: pthread_destroy\n"));
	return (0);
}
