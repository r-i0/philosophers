/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:29:34 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 11:29:35 by rsudo            ###   ########.fr       */
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
