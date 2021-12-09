/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:42 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 23:09:00 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_end(t_rule *rule)
{
	bool	end;

	end = false;
	pthread_mutex_lock(&(rule->mu_end));
	if (rule->end == true)
	{
		end = true;
	}
	pthread_mutex_unlock(&(rule->mu_end));
	return (end);
}

bool	is_die(t_rule *rule, t_philo *philo)
{
	bool	die;

	die = false;
	pthread_mutex_lock(&(rule->mu_time));
	if (get_ms_timestamp() - philo->time_last_eat > rule->time_die)
	{
		die = true;
	}
	pthread_mutex_unlock(&(rule->mu_time));
	return (die);
}

bool	is_all_philos_ate(t_rule *rule)
{
	int		i;
	bool	ate;

	i = 0;
	ate = true;
	pthread_mutex_lock(&(rule->mu_time));
	if (rule->times_must_eat == -1)
	{
		pthread_mutex_unlock(&(rule->mu_time));
		return (false);
	}
	while (i < rule->nb_philo)
	{
		if (rule->philo[i].cnt_eat < rule->times_must_eat)
			ate = false;
		i++;
	}
	pthread_mutex_unlock(&(rule->mu_time));
	return (ate);
}

void	*observer(void *philo_ptr)
{
	t_philo	*philo;
	t_rule	*rule;

	philo = philo_ptr;
	rule = philo->rule;
	while (1)
	{
		if (is_end(rule))
			break ;
		if (is_all_philos_ate(rule))
		{
			pthread_mutex_lock(&(rule->mu_end));
			rule->end = true;
			pthread_mutex_unlock(&(rule->mu_end));
			break ;
		}
		if (is_die(rule, philo))
		{
			philo_die(philo);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
