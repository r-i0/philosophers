/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:11:48 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/01 12:14:40 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *philo_ptr)
{
	t_info	*info;
	t_philo	*philo;

	philo = philo_ptr;
	info = philo->info;
	if (philo->nb % 2)
	{
		usleep(500);
	}
	while (1)
	{
		pthread_mutex_lock(&(info->mu_end));
		if (info->end == true)
		{
			pthread_mutex_unlock(&(info->mu_end));
			break ;
		}
		pthread_mutex_unlock(&(info->mu_end));
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

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

int	join_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(info->philo[i].thread, NULL) != 0)
			return (-1);
		if (pthread_join(info->philo[i].death_thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

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

/* void end(void)__attribute__((destructor)); */

/* void end(void) */
/* { */
/*     system("leaks philo"); */
/* } */

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (ft_puterror("invalid argument\n"));
	if (philo_init(argv, &info))
		return (ft_puterror("error: init\n"));
	if (start_dining(&info) == -1)
		return (ft_puterror("error: pthread_create\n"));
	if (join_thread(&info))
		return (ft_puterror("error: pthread_join\n"));
	if (free_info(&info))
		return (ft_puterror("error: pthread_destroy\n"));
	return (0);
}
