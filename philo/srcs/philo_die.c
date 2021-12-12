/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:45:29 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/12 23:45:30 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_die(t_philo *philo)
{
	t_rule				*rule;
	const unsigned long	timestamp = get_ms_timestamp();

	rule = philo->rule;
	pthread_mutex_lock(&(rule->mu_end));
	if (rule->end == false)
	{
		printf("%lu %d died\n", timestamp, philo->nb);
		rule->end = true;
	}
	pthread_mutex_unlock(&(rule->mu_end));
}
