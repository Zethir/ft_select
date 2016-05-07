/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 21:11:14 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/07 17:59:13 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		clean_lst(void)
{
	tputs(tgetstr("rc", NULL), 0, ft_putchar_int);
	tputs(tgetstr("cd", NULL), 0, ft_putchar_int);
}

static char	*join_select(t_intel *node)
{
	t_lst	*ptr;
	char	*str;

	ptr = node->head;
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

static char	*deal_with_input(t_intel *node, t_struct *info)
{
	char	*str;

	deal_with_arrow(info);
	if (*info->buff == 10)
	{
		clean_lst();
		str = join_select(node);
		return (str);
	}
	if (info->buff[0] == 27 && info->buff[1] == 0)
	{
		clean_lst();
		reset_term();
		exit (-1);
	}
	return (NULL);
}

void		print_lst(t_intel *node, t_struct *info)
{
	t_lst	*ptr;

	ptr = node->head;
	clean_lst();
	info->index[1] = 1;
	info->index[0] = 0;
	info->nb_item = (node->length - 1) / info->col;
	if (((node->length - 1) % info->col) != 0)
		info->nb_item += 1;
	info->k = info->nb_item;
	while (ptr)
	{
		if (info->index[1] == info->k + 1)
			info->index[1] = 1;
		deal_with_col(node, info); 
		print_opt(node, ptr, info);
		info->index[1] += 1;
		if (!ptr->next)
			info->realcol = info->coeff;
		ptr = ptr->next;
	}
}

char		*deal_with_term(t_intel *node, t_struct *info)
{
	char			*str;

	info->coeff = 0;
	if (read(0, info->buff, BUFF_SIZE) == -1)
		exit (-1);
	info->nb_item = (node->length - 1) / info->col;
	if (((node->length - 1) % info->col) != 0)
		info->nb_item += 1;
	info->j = info->nb_item;
	str = deal_with_input(node, info);
	if (str)
		return (str);
	info->size_last = 0;
	print_lst(node, info);
	ft_bzero(info->buff, BUFF_SIZE);
	return (NULL);
}
