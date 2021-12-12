/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:45:36 by rsudo             #+#    #+#             */
/*   Updated: 2021/12/12 23:45:37 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	const unsigned long	timestamp = put_act(philo, "is sleeping");

	if (timestamp != 0)
	{
		acc_sleep(philo->rule->time_sleep);
	}
}
