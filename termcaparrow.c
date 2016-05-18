/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 20:12:50 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/18 16:40:50 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	deal_with_left(t_struct *info, t_lst *ptr)
{
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 68)
	{
		while (ptr->line != 1)
			ptr = ptr->next;
		ptr->line = 0;
		if (!ptr->prev)
		{
			ptr = info->node->tail;
			ptr->line = 1;
		}
		else
			left_arrow(info, ptr);
	}
}

static void	deal_with_right(t_struct *info, t_lst *ptr)
{
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 67)
	{
		while (ptr->line != 1)
			ptr = ptr->next;
		ptr->line = 0;
		if (!ptr->next)
		{
			ptr = info->node->head;
			ptr->line = 1;
		}
		else
			right_arrow(info, ptr);
	}
}

static void	deal_with_down(t_struct *info, t_lst *ptr)
{
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 66)
	{
		while (ptr->line != 1)
			ptr = ptr->next;
		ptr->line = 0;
		if (!ptr->next)
		{
			ptr = info->node->head;
			ptr->line = 1;
		}
		else
			ptr->next->line = 1;
	}
}

static void	deal_with_up(t_struct *info, t_lst *ptr)
{
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 65)
	{
		while (ptr->line != 1)
			ptr = ptr->next;
		ptr->line = 0;
		if (!ptr->prev)
		{
			ptr = info->node->tail;
			ptr->line = 1;
		}
		else
			ptr->prev->line = 1;
	}
}

void		deal_with_arrow(t_struct *info)
{
	t_lst	*ptr;

	ptr = info->node->head;
	deal_with_up(info, ptr);
	deal_with_down(info, ptr);
	deal_with_left(info, ptr);
	deal_with_right(info, ptr);
}
