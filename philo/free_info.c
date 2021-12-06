/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:43:47 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/06 12:43:48 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_info(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_mutex_destroy(&(info->fork[i])) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&(info->mu_time)))
		return (-1);
	if (pthread_mutex_destroy(&(info->mu_end)))
		return (-1);
	free(info->philo);
	free(info->fork);
	return (0);
}
