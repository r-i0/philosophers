/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:38:29 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/10 10:14:26 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_one_philo(t_rule *rule)
{
	pthread_mutex_lock(&rule->mu_time);
	if (rule->nb_philo == 1)
	{
		pthread_mutex_unlock(&rule->mu_time);
		return (true);
	}
	pthread_mutex_unlock(&rule->mu_time);
	return (false);
}

static void	*one_philo(t_rule *rule, t_philo *philo)
{
	pthread_mutex_lock(&(rule->mu_fork[philo->left_fork]));
	put_act(philo, "has taken a fork");
	pthread_mutex_unlock(&(rule->mu_fork[philo->left_fork]));
	while (1)
	{
		pthread_mutex_lock(&(rule->mu_end));
		if (rule->end == true)
		{
			pthread_mutex_unlock(&(rule->mu_end));
			break ;
		}
		pthread_mutex_unlock(&(rule->mu_end));
	}
	return (NULL);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	if (is_one_philo(philo->rule))
		return (one_philo(philo->rule, philo));
	if (philo->nb % 2)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&(philo->rule->mu_end));
		if (philo->rule->end == true)
		{
			pthread_mutex_unlock(&(philo->rule->mu_end));
			break ;
		}
		pthread_mutex_unlock(&(philo->rule->mu_end));
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
