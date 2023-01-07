/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzirh <zzirh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:34:22 by zzirh             #+#    #+#             */
/*   Updated: 2022/10/16 11:02:39 by zzirh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

long long	ft_get_time(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	ft_sleepin(long long time)
{
	long long	t_time;
	long long	s_time;

	s_time = ft_get_time() + time;
	t_time = ft_get_time();
	while (t_time < s_time)
	{
		usleep(100);
		t_time = ft_get_time();
	}
}

void	ft_eatin(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->id % phil->data->nbr_of_ph]);
	pthread_mutex_lock(&phil->data->lock);
	printf("%lld %d has taken a fork\n",
		(ft_get_time() - phil->data->stime), phil->id);
	pthread_mutex_unlock(&phil->data->lock);
	pthread_mutex_lock(&phil->data->forks[phil->id - 1]);
	pthread_mutex_lock(&phil->data->lock);
	printf("%lld %d has taken a fork\n",
		(ft_get_time() - phil->data->stime), phil->id);
	pthread_mutex_unlock(&phil->data->lock);
	pthread_mutex_lock(&phil->data->lock);
	printf("%lld %d is eating\n",
		(ft_get_time() - phil->data->stime), phil->id);
	if (phil->cmt_meal > 0)
		phil->cmt_meal--;
	pthread_mutex_unlock(&phil->data->lock);
	phil->lt_meal = ft_get_time();
	phil->eatin = 0;
	ft_sleepin(phil->data->t_to_eat);
	phil->eatin = 1;
	pthread_mutex_unlock(&phil->data->forks[phil->id - 1]);
	pthread_mutex_unlock(&phil->data->forks[phil->id % phil->data->nbr_of_ph]);
}

void	*ft_philo_routine(void *info)
{
	t_philo	*phil;

	phil = (t_philo *)info;
	if (phil->id % 2)
		usleep(500);
	while (1)
	{
		ft_eatin(phil);
		pthread_mutex_lock(&phil->data->lock);
		printf("%lld %d is sleeping\n",
			(ft_get_time() - phil->data->stime), phil->id);
		pthread_mutex_unlock(&phil->data->lock);
		ft_sleepin(phil->data->t_to_sleep);
		pthread_mutex_lock(&phil->data->lock);
		printf("%lld %d is thinking\n",
			(ft_get_time() - phil->data->stime), phil->id);
		pthread_mutex_unlock(&phil->data->lock);
	}
	return (phil);
}

int	ft_dead(t_philo *info, t_data *args)
{
	int	i;
	int	c;

	while (1)
	{
		i = 0;
		c = 0;
		while (i < args->nbr_of_ph)
		{
			if (((ft_get_time() - info[i].lt_meal) > args->t_to_die)
				&& (info[i].eatin))
			{
				pthread_mutex_lock(&args->lock);
				printf("%lld %d died\n",
					(ft_get_time() - args->stime), info[i].id);
				return (1);
			}
			c += (info[i].cmt_meal);
			i++;
		}
		if (c == 0)
			return (1);
	}
	return (0);
}
