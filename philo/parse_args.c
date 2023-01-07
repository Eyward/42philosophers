/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzirh <zzirh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 23:20:49 by zzirh             #+#    #+#             */
/*   Updated: 2022/10/21 21:42:01 by zzirh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	check_av(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] > 32)
	{
		if (!ft_isdigit(s[i]))
			return (2);
		i++;
	}
	if (s[i] != '0')
		return (0);
	while (s[i])
	{
		if (s[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if ((ac != 5 && ac != 6))
		return (1);
	if (ac == 5 || ac == 6)
	{		
		while (av[i])
		{
			if (check_av(av[i]) == 1)
				i++;
			if (check_av(av[i]) == 2)
			{
				printf("Invalid arguments\n");
				return (1);
			}
			if (av[i] == NULL || !ft_atoi(av[i]))
			{
				printf("Invalid arguments\n");
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	ft_init_args(t_data **args, char **av)
{
	int	i;

	i = 0;
	if (!(*args))
		return (0);
	(*args)->nbr_of_ph = ft_atoi(av[1]);
	(*args)->t_to_die = ft_atoi(av[2]);
	(*args)->t_to_eat = ft_atoi(av[3]);
	(*args)->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		(*args)->nbr_of_times_eat = ft_atoi(av[5]);
	else
		(*args)->nbr_of_times_eat = -1;
	(*args)->forks = malloc(sizeof(pthread_mutex_t) * (*args)->nbr_of_ph);
	if (!((*args)->forks))
		return (0);
	while (i < (*args)->nbr_of_ph)
	{
		if (pthread_mutex_init(&(*args)->forks[i], NULL))
			return (0);
		i++;
	}
	pthread_mutex_init(&(*args)->lock, NULL);
	return (1);
}

t_philo	*ft_init_info(t_philo *info, t_data *args)
{
	int	i;

	i = 0;
	if (!info)
		return (0);
	while (i < args->nbr_of_ph)
	{
		info[i].id = i + 1;
		info[i].data = args;
		info[i].lt_meal = args->stime;
		info[i].cmt_meal = args->nbr_of_times_eat;
		info[i].eatin = 1;
		i++;
	}
	return (info);
}
