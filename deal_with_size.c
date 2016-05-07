/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 18:22:56 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/07 18:05:25 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		deal_with_col(t_intel *node, t_struct *info)
{
	if (info->nb_item == 0)
	{
		info->coeff += 1;
		info->nb_item = (node->length - 1) / info->col;
		info->index[0] += 1;
		if (((node->length - 1) % info->col) != 0)
			info->nb_item += 1;
		tputs(tgoto(tgetstr("RI", NULL), 0, (info->nb_col + 2) * info->coeff), 1, ft_putchar_int);
		tputs(tgoto(tgetstr("UP", NULL), 0, info->nb_item), 1, ft_putchar_int);
	}
	else if (info->coeff > 0)
		tputs(tgoto(tgetstr("RI", NULL), 0, (info->nb_col + 2) * info->coeff), 1, ft_putchar_int);
	if (info->coeff == info->realcol)
		info->size_last += 1;
	info->nb_item -= 1;
}

void		longest_word(t_intel *node, t_struct *info)
{
	t_lst	*ptr;

	ptr = node->head;
	info->nb_col = 0;
	while (ptr)
	{
		if (ptr->len > info->nb_col)
			info->nb_col = ptr->len;
		ptr = ptr->next;
	}
	info->col = info->col / (info->nb_col + 2);
}
