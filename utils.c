/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:07:31 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/06 11:06:11 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (1);
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
