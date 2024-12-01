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

typedef struct s_data
{
	int	total_nmb;
	int	thread_number;
	int	forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	pthread_t	thread;
	// mutex curr
	// mutex right
	// ?? mutex left
}				t_data;

typedef struct s_big
{
	//size_t	nmb;
	t_list	*ph_list;
}					t_big;

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

//np_arg.c
void	check_number_arg(int argc);
//pars.c
int		init_big_struct(t_big *big); // char **argv, 
//pars_fill_big_list.c
int		fill_big_list(char **argv, t_big **big);
//calloc.c
void	*ft_new_calloc(size_t nmemb, size_t size);
void	ft_new_putstr_fd(char *s, int fd);
//analys_args.c
int		analys_args(char **argv);
//debug.c
void    print_my_list(t_big *big);
//cleanup.c
void	ft_free_cl(t_list **ll);

#endif
