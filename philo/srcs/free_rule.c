/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:43:47 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 23:09:00 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_rule(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->nb_philo)
	{
		if (pthread_mutex_destroy(&(rule->mu_fork[i])) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&(rule->mu_time)))
		return (-1);
	if (pthread_mutex_destroy(&(rule->mu_end)))
		return (-1);
	free(rule->philo);
	free(rule->mu_fork);
	free(rule->fork);
	return (0);
}
