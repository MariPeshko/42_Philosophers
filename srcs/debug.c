/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:13:37 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/01 23:14:47 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_my_list(t_big *big)
{
    t_big *cpy;
	t_list *cp_lst;
    t_data *cp_data;
    
	cpy = big;
	cp_lst = cpy->ph_list;
	while (cp_lst)
	{
        cp_data = (t_data *)cp_lst->content;
		printf("check nodes: thread number %d\n", cp_data->thread_number);
		cp_lst = cp_lst->next;
	}
}