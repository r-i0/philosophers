/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:07:31 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/09 09:37:15 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	put_act(t_philo *philo, char *msg)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&(philo->rule->mu_end));
	if (philo->rule->end == true)
	{
		pthread_mutex_unlock(&(philo->rule->mu_end));
		return (0);
	}
	timestamp = get_ms_timestamp();
	printf("%lu %d %s\n", timestamp, philo->nb, msg);
	pthread_mutex_unlock(&(philo->rule->mu_end));
	return (timestamp);
}

unsigned long	get_ms_timestamp(void)
{
	struct timeval	tv;
	int				ret;

	ret = gettimeofday(&tv, NULL);
	if (ret != 0)
	{
		ft_putstr_fd("error: gettimeofday\n", STDERR_FILENO);
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_puterror(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	acc_sleep(unsigned long ms)
{
	const unsigned long	time_end = get_ms_timestamp() + ms;
	unsigned long		timestamp;

	timestamp = get_ms_timestamp();
	while (timestamp <= time_end)
	{
		usleep(100);
		timestamp = get_ms_timestamp();
	}
	return (0);
}
