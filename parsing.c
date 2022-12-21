/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:40:48 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/21 11:18:11 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc > 6 || argc < 5)
		return (0);
	i = 0;
	while (i < argc - 1)
	{
		if (!check_str(argv[1]))
			return (0);
		i++;
	}
	return (1);
}

t_const_philo	*get_args(t_const_philo *data, int argc, char **argv)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->total_ate = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->time = get_time();
	return (data);
}

void	get_params(t_philo *philo, t_const_philo *data,
pthread_mutex_t *mutex, pthread_mutex_t *print)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philo[i].ate = 0;
		philo[i].id = i;
		philo[i].mutex = mutex;
		philo[i].print = print;
		philo[i].data = data;
		i++;
	}
}

void	init_parameters(t_philo *philo, t_const_philo *data)
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	print;
	int				i;

	i = 0;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!mutex)
		return ;
	while (i < data->num_philo)
		if (pthread_mutex_init(&mutex[i++], 0))
			return ;
	if (pthread_mutex_init(&print, 0))
		return ;
	get_params(philo, data, mutex, &print);
}
