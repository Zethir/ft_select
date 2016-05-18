/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 21:11:14 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/18 18:10:44 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		clean_lst(t_struct *info)
{
	tputs(tgetstr("rc", NULL), 0, ft_putchar_int);
	tputs(tgetstr("cd", NULL), 0, ft_putchar_int);
	info->coeff = 0;
	info->len = 0;
	info->size_last = 0;
	info->count = info->node->length;
}

static char	*join_select(t_struct *info)
{
	t_lst	*ptr;
	char	*str;

	ptr = info->node->head;
	str = ft_strdup("");
	while (ptr)
	{
		if (ptr->save)
		{
			str = ft_strjoin(str, ptr->save);
			str = ft_strjoin(str, " ");
		}
		ptr = ptr->next;
	}
	return (str);
}

static char	*deal_with_input(t_struct *info)
{
	char	*str;

	deal_with_arrow(info);
	start_end(info);
	if (*info->buff == 10)
	{
		clean_lst(info);
		str = join_select(info);
		free_lst(info);
		return (str);
	}
	if (info->buff[0] == 27 && info->buff[1] == 0)
	{
		clean_lst(info);
		free_lst(info);
		reset_term(info);
		exit(-1);
	}
	if (info->buff[0] == 127 || (info->buff[0] == 27 && info->buff[1] == 91
				&& info->buff[2] == 51))
		del_elem_from_list(info);
	return (NULL);
}

void		print_lst(t_struct *info)
{
	t_lst	*ptr;

	ptr = info->node->head;
	clean_lst(info);
	while (ptr)
	{
		deal_with_col(info);
		print_opt(ptr, info);
		info->len++;
		if (info->len == info->node->length)
			info->realcol = info->coeff;
		ptr = ptr->next;
	}
}

char		*deal_with_term(t_struct *info)
{
	char	*str;

	if (read(0, info->buff, BUFF_SIZE) == -1)
		exit(-1);
	info->nb_item = (info->node->length) / info->nb_col;
	if (((info->node->length) % info->nb_col) != 0)
		info->nb_item += 1;
	str = deal_with_input(info);
	if (str)
		return (str);
	print_lst(info);
	ft_bzero(info->buff, BUFF_SIZE);
	return (NULL);
}
