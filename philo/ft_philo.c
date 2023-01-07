/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzirh <zzirh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 21:35:56 by zzirh             #+#    #+#             */
/*   Updated: 2022/10/21 22:49:20 by zzirh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

pthread_t	*philo_allocate(int num_phil)
{
	pthread_t	*philo;

	philo = malloc(sizeof(pthread_t) * num_phil);
	if (!philo)
		return (0);
	return (philo);
}

int	main(int ac, char	**av)
{
	t_data		*args;
	t_philo		*info;
	pthread_t	*philo;
	int			i;

	i = 0;
	if (ft_check_args(ac, av))
		return (1);
	args = malloc(sizeof(t_data));
	if (!ft_init_args(&args, av))
		return (1);
	info = malloc(sizeof(t_philo) * args->nbr_of_ph);
	args->stime = ft_get_time();
	info = ft_init_info(info, args);
	philo = philo_allocate(args->nbr_of_ph);
	while (i < args->nbr_of_ph)
	{
		if (pthread_create(&philo[i], NULL, ft_philo_routine, &info[i]) != 0)
			return (1);
		pthread_detach(philo[i]);
		i++;
	}
	if (ft_dead(info, args))
		return (ft_free(info, args, philo));
}
