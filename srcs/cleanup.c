/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:50:32 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 00:52:37 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free_cl(t_list **ll)
{
    t_list	*temp;
	t_list	*curr;
	t_data	*comm_info;

	if (*ll != NULL)
		curr = *ll;
	else
	{
		temp = NULL;
		curr = NULL;
		comm_info = NULL;
	}
	while (curr != NULL)
	{
		temp = curr;
		comm_info = temp->content;
		curr = curr->next;
		free(comm_info);
        // pthread_mutex_destroy
		free(temp);
		temp = NULL;
	}
	*ll = NULL;
}