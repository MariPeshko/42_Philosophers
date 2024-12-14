/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:45:44 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/23 19:45:44 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// to avoid duplications
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// wrrite
# include <unistd.h>
// memset
# include <stdlib.h>
// printf
# include <stdio.h>
// 
# include <pthread.h>
//
# include <sys/time.h>
//to use data type bool
# include <stdbool.h>
// memset
# include <string.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;
typedef enum e_status	t_status;

enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	DEAD,
	DONE
};

struct s_philo
{
	t_table			*tbl;
	pthread_t		thread_t;
	int				philo_id;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	t_status		status;
	unsigned long	time_last_meal;
	long			amount_meal;
};

struct s_table
{
	int				total_nmb;
	unsigned long	time_die;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	unsigned long	time_think;
	unsigned long	start_time;
	pthread_mutex_t	mtx_time;
	pthread_mutex_t	mtx_dead;
	pthread_mutex_t	mtx_msg;
	pthread_mutex_t	**f_mtxs;
	struct s_philo	**philos;
	bool			dead;
	unsigned long	minimum_meal;
	bool			all_full;
	pthread_t		monitor;
};

//parsing_01.c
int				check_args(char **argv);
//parsing_02.c
int				check_number_arg(int argc);
int				init_table(char **argv, t_table *table);
//parsing_03_mtx.c
int				init_mtx(t_table *table);
//init_philosophers.c
int				init_philosophers(t_table *table);
//dining.c
int				start_dining(t_table *table);
void			set_start_time(t_table *tbl);
int				ft_wait(t_table *tbl);
//dining_monitor.c
void			*monitor(void *arg);
int				monitor_in_loop(t_table *tbl);
//routine_01.c
void			*routine(void *arg);
int				ft_fork(t_philo *philo);
int				ft_eat(t_philo *philo);
int				ft_sleep(t_philo *philo);
int				ft_think(t_philo *philo);
//routine_02.c
int				routine_even(t_philo *philo);
int				routine_odd(t_philo *philo);
int				ft_msg_second_fork(t_philo *philo);
//routine_one_phil.c
void			*routine_one(void *arg);
//is_dead.c
int				dead_or_full(t_table *tbl);
int				is_dead_monitor(t_philo *philo);
//all_full.c
int				all_full(t_table *table);
//msg.c
void			ft_msg(t_philo *philo, unsigned long time, t_status st);
//time.c
int				ft_usleep(unsigned long time);
unsigned long	curr_time(void);
unsigned long	time_to_think(int t_nmb);
unsigned long	ft_timestamp(t_table *tbl);
unsigned long	ft_time_last_meal(t_table *tbl);
//ft_calloc.c
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_new_putstr_fd(char *s, int fd);
//cleanup.c
void			destroy_mtx(t_table *table);
void			free_philos(t_philo **philos, int total_nmb);
//ft_isdigit.c
int				ft_isdigit(int c);
//ft_atoi.c
int				ft_atoi(const char *str);
//ft_putchar_fd.c
void			ft_putchar_fd(char c, int fd);

#endif
