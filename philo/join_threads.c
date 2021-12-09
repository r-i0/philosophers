/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:43:55 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 23:09:00 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->nb_philo)
	{
		if (pthread_join(rule->philo[i].thread, NULL) != 0)
			return (-1);
		if (pthread_join(rule->philo[i].death_thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
