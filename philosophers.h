/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:37:22 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/22 13:49:02 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <assert.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_phil
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				total_ate;
	unsigned long	time;
}t_const_philo;

typedef struct s_philo
{
	int				ate;
	int				id;
	t_const_philo	*data;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	pthread_mutex_t	*eat;
	unsigned long	last_meal;
}t_philo;

int				check_args(int argc, char **argv);
int				check_str(char *str);
int				ft_atoi(const char *str);
t_const_philo	*get_args(t_const_philo *data, int argc, char **argv);
unsigned long	get_time(void);
void			init_parameters(t_philo *philo, t_const_philo *data);
void			get_params(t_philo *philo, t_const_philo *data, \
pthread_mutex_t *mutex, pthread_mutex_t *print, pthread_mutex_t *eat);
void			print(t_philo *philo, unsigned long time, char *action);
void			clean_mutex(t_philo *philo);

#endif