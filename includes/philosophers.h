/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:22:35 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/15 15:59:40 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

/* Status */
# define MSG_EATING		1
# define MSG_FORK		2
# define MSG_SLEEPING	3
# define MSG_THINKING	4
# define MSG_DIE		5

typedef struct s_data t_data;

typedef struct s_philo {
	t_data			*data;
	int				tid;
	pthread_t		ptr;
	long long int	start;
	int				left;
	int				right;
	pthread_mutex_t	lock_last_meal;
	long long int	last_meal;
}	t_philo;

typedef struct s_data {
	int				philo_nb;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				must_eat;
	t_philo			*philos;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	go_mutex;
	pthread_t		death_thread;
	pthread_mutex_t	is_dead_mutex;
	bool				is_dead;
}	t_data;

/* Parsing.c */
t_data		*parse(int argc, char **argv);

/* Threads.c */
int		lauch_threads(t_data *data);
int			join_threads(t_data *data);
void		*routine(void *arg);

/* Libft-addons.c */
long int	ft_atol(char *s);
int			ft_atoi(const char *s);
int			ft_is_positive(int num);
int			ft_is_int(long int num);
int			ft_isdigit(int c);
size_t		ft_putstr_fd(char *s, int fd);
size_t		ft_putchar_fd(char c, int fd);
size_t		ft_putnbr_fd(long long int n, int fd);

/* Init.c */
t_data	*init_data(char **args);
int		create_chopsticks(t_data *data);
int		create_philos(t_data *data);
int		create_threads(t_data *data);
int		create_mutexes(t_data *data);

/* Prints.c */
void	print_error(char *message);
void	print_status(int status, t_philo *philo);

/* Time.c */
void	assign_philo_lastmeal(t_data *data, long long int last_meal);
void	assign_philo_start(t_data *data, long long int start);
void	wait_till_time(long long int time);

/* Actions.c */
void	wait_and_take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

/* Deaths */
void	*death_routine(void *arg);
int		is_dead(t_data *data);

#endif
