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

// memset
#include <stdlib.h>
// printf
#include <stdio.h>
// 
#include <pthread.h>

//unistd.h (for write) is included in libft.h
# include "../libft/include/libft.h"
# include "../libft/include/libft_bonus.h"

//to use data type bool
# include <stdbool.h>
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

//define a global variable for signal-handling
extern int	g_signalnum;

//01_pre_prompt/pre_prompt.c
// t_big		*init_t_big(char **envp);
// char		**copy_envp(char **envp);
// int			ft_spacetabchecker(char *input);
// void		ft_welcome(void);

#endif
