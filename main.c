/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:56:36 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/21 10:14:53 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print(t_philo *philo, unsigned long time, char *action)
{
	pthread_mutex_lock(philo->print);
	printf("%lums, %d %s\n", time, philo->id, action);
}

void	clean_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philo)
		pthread_mutex_destroy(&philo->mutex[i++]);
}

void	*action(void *philo_void)
{
	t_philo	*philo;
	
	philo = (t_philo *)philo_void;
	if (philo->id % 2 == 0)
		usleep(10);
	philo->last_meal = get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[philo->id - 1]);
		print(philo, get_time() - philo->data->time, "has taken a fork");
		pthread_mutex_lock(&philo->mutex[philo->id % philo->data->num_philo]);
		print(philo, get_time() - philo->data->time, "has taken a fork");
		print(philo, get_time() - philo->data->time, "is eating");
		philo->ate += 1;
		if (philo->ate == philo->data->must_eat)
			philo->data->total_ate++;
		usleep(philo->data->time_eat * 1000);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->id % philo->data->num_philo]);
		print(philo, get_time() - philo->data->time, "is sleeping");
		usleep(philo->data->time_sleep * 1000);
		print(philo, get_time() - philo->data->time, "is thinking");
	}
}
void	live_and_die(t_philo *philo, t_const_philo *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo[i].data->total_ate == philo[i].data->num_philo)
		{
			clean_mutex(philo);
			return ;
		}
		if (get_time() - philo[i].last_meal > (unsigned long)data->time_die)
		{
			usleep(100);
			print(philo, get_time() - philo->data->time, "died");
			clean_mutex(philo);
			return ;
		}
		i = (i + 1) % data->num_philo;
		usleep(500);
	}
}

int main(int argc, char **argv)
{
	t_const_philo	*data;
	t_philo			*philo;
	pthread_t		*thread;
	int				i;

	if (check_args(argc, argv))
	{
		data = (t_const_philo *)malloc(sizeof(t_const_philo));
		if (!data)
			return (0);
		data = get_args(data, argc, argv);
	}
	else
		return (printf("ERROR\n"), 1);
	philo = (t_philo *)malloc(sizeof(t_philo) * data->num_philo);
	if	(!philo)
		return (0);
	init_parameters(philo, data);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data->num_philo);
	i = 0;
	while (i < data->num_philo - 1)
	{
		pthread_create(&thread[i], NULL, action, philo + i);
		usleep(100);
		i++;
	}
	live_and_die(philo, data);
	free(thread);
	return (0);
}