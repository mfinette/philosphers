/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:56:36 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/21 08:56:28 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print(t_philo *philo, unsigned long time, char *action)
{
	pthread_mutex_lock(philo->print);
	printf("%lums, %d %s\n", time, philo->id, action);
}

void	action(void *philo_void)
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
		
	}
}
void	live_and_die(t_philo *philo, t_const_philo *data);

int main(int argc, char **argv)
{
	t_const_philo	*data;
	t_philo			*philo;
	pthread_t		*thread;
	int				i;

	if (check_args(argc, argv))
	{
		data = (t_const_philo *)malloc(sizeof(t_const_philo));
		data = get_args(argc, argv);
	}
	else
		return (printf("ERROR\n"), 1);
	philo = (t_philo *)malloc(sizeof(t_philo) * data->num_philo);
	if	(!philo)
		return (0);
	init_parameters(philo, data);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data->num_philo);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_create(&thread[i], NULL, action, philo + i);
		usleep(100);
		i++;
	}
	live_and_die(philo, data);
	free(thread);
	return (0);
	//printf("data recieved =\nnb of philo = %d\ntime_die = %d\ntime_eat = %d\ntime_sleep = %d\n", data.num_philo, data.time_die, data.time_eat, data.time_sleep);
}