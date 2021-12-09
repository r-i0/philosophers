/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:12:33 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/08 23:36:57 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_rule *rule)
{
	int					i;
	const unsigned long	start_time = get_ms_timestamp();

	i = 0;
	while (i < rule->nb_philo)
	{
		pthread_mutex_init(&rule->mu_fork[i], NULL);
		rule->philo[i].nb = i + 1;
		rule->philo[i].right_fork = i;
		rule->philo[i].left_fork = (i + 1) % rule->nb_philo;
		rule->philo[i].rule = rule;
		rule->philo[i].time_last_eat = start_time;
		rule->philo[i].cnt_eat = 0;
		rule->fork[i] = false;
		i++;
	}
}

static int	allocate_rule(t_rule *rule)
{
	rule->philo = malloc(sizeof(t_philo) * (rule->nb_philo));
	if (rule->philo == NULL)
		return (-1);
	rule->mu_fork = malloc(sizeof(pthread_mutex_t) * (rule->nb_philo));
	if (rule->mu_fork == NULL)
	{
		free(rule->philo);
		return (-1);
	}
	rule->fork = malloc(sizeof(bool) * (rule->nb_philo));
	if (rule->fork == NULL)
	{
		free(rule->philo);
		free(rule->mu_fork);
		return (-1);
	}
	return (0);
}

static bool	validate_rule(int argc, t_rule *rule, bool err)
{
	if (err || rule->nb_philo < 1
		|| rule->time_die < 1
		|| rule->time_eat < 1
		|| rule->time_sleep < 1
		|| (argc == 6 && rule->times_must_eat < 1))
	{
		return (true);
	}
	if (rule->time_eat > 1000
		|| rule->time_sleep > 1000)
	{
		return (true);
	}
	return (false);
}

static bool	init_rule(int argc, char **argv, t_rule *rule)
{
	bool	err;

	err = false;
	rule->times_must_eat = -1;
	rule->end = false;
	rule->nb_philo = ft_atoui(argv[1], &err);
	rule->time_die = (unsigned long)ft_atoui(argv[2], &err);
	rule->time_eat = ft_atoui(argv[3], &err);
	rule->time_sleep = ft_atoui(argv[4], &err);
	if (argc == 6)
		rule->times_must_eat = ft_atoui(argv[5], &err);
	if (validate_rule(argc, rule, err))
		return (true);
	if (allocate_rule(rule) == -1)
		return (true);
	if (pthread_mutex_init(&(rule->mu_time), NULL))
		return (true);
	if (pthread_mutex_init(&(rule->mu_end), NULL))
	{
		pthread_mutex_destroy(&(rule->mu_time));
		return (true);
	}
	return (err);
}

bool	philo_init(int argc, char **argv, t_rule *rule)
{
	bool	err;

	err = init_rule(argc, argv, rule);
	if (!err)
	{
		init_philo(rule);
	}
	return (err);
}
