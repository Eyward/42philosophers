/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzirh <zzirh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 21:27:24 by zzirh             #+#    #+#             */
/*   Updated: 2022/10/21 22:43:41 by zzirh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				nbr_of_ph;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nbr_of_times_eat;
	long long		stime;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;	
}	t_data;

typedef struct s_philo
{
	int			id;
	long long	lt_meal;
	int			eatin;
	int			cmt_meal;
	t_data		*data;
}	t_philo;

int			ft_check_args(int ac, char **av);
int			ft_init_args(t_data **args, char **av);
t_philo		*ft_init_info(t_philo *info, t_data *args);
long long	ft_get_time(void);
void		ft_eatin(t_philo *phil);
void		ft_sleepin(long long time);
void		*ft_philo_routine(void *info);
int			ft_dead(t_philo *info, t_data *args);
int			ft_strncmp(char *s1, char *s2);
int			ft_atoi(char *str);
int			ft_isdigit(int c);
int			ft_free(t_philo *info, t_data *args, pthread_t *philo);

#endif
