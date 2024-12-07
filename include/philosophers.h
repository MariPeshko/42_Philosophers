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

//unistd.h (for write) is included in libft.h
# include "../libft/include/libft.h"
# include "../libft/include/libft_bonus.h"

// memset
#include <stdlib.h>
// printf
#include <stdio.h>
// 
#include <pthread.h>
//
#include <sys/time.h>
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
	DEAD,
	DONE
};

struct s_philo
{
	t_table			*tbl;
	pthread_t		thread_t;
	int				philo_id;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	t_status		status;
	unsigned long	time_last_meal;
	long			amount_meal;
};

struct s_table
{
	int				total_nmb;
	unsigned long			time_die;
	unsigned long			time_eat;
	unsigned long			time_sleep;
	unsigned long	start_time;
	pthread_mutex_t	mtx_time;
	pthread_mutex_t	mtx_dead;
	pthread_mutex_t	mtx_msg;
	pthread_mutex_t **f_mtxs;
	struct s_philo	**philos;
	bool			dead;
	unsigned long			minimum_meal;
	bool			all_full;
	pthread_t		loop_thread;
};

//to provide a standardized way to report and interpret error conditions
# include <errno.h>
//to be able to work with function waitpid
# include <sys/wait.h>
// to be able to work with function readline
// we also have to include -lreadline to our Makefile
// to consider readline while compiling
# include <readline/history.h>
# include <readline/readline.h>
//to handle signals
# include <signal.h>
// to use struct sigaction
# include <bits/sigaction.h>
// function ioctl, macros TIOCSTI
# include <sys/ioctl.h>
//to change behaviour of the terminal (not-printing all control squences)
# include <termios.h>
// for S_ISDIR macro in is_valid_cmd_and_print_err function
# include <sys/stat.h>
//define error message
# define INPUT_ERROR "Not correct number of input arguments\
to execute minishell\n"

//for testing reasons:
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes 
//--track-fds=yes --suppressions=suppressions.supp ./minishell

//check_nmb_argc.c
int		check_number_arg(int argc);
//analys_args.c
int		analys_args(char **argv);
//pars.c
int		init_table(char **argv, t_table *table);
//pars_fill_big_list.c
int		init_mtx(t_table *table);
//init_philosophers.c
int		init_philosophers(t_table *table);
//dining.c
int		start_dining(t_table *table);
//routine_one.c
void	*routine_one(void *arg);
//is_dead.c
int		is_dead(t_philo *philo);
int		is_dead_monitor(t_philo *philo);
//all_full.c
int		all_full(t_table *table);
//time.c
int		ft_usleep(unsigned long time);
unsigned long	curr_time();

//calloc.c
void	*ft_new_calloc(size_t nmemb, size_t size);
void	ft_new_putstr_fd(char *s, int fd);
//debug.c
void	print_tests(t_table *table);
//cleanup.c
void	destroy_mtx(t_table *table);
void	free_philos(t_philo **philos, int total_nmb);

#endif
