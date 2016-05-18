/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 18:22:56 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/18 16:34:54 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		deal_with_col(t_struct *info)
{
	if (info->nb_item == 0)
	{
		info->coeff += 1;
		info->nb_item = (info->node->length) / info->nb_col;
		if (((info->node->length) % info->nb_col) != 0)
			info->nb_item += 1;
		tputs(tgoto(tgetstr("RI", NULL), 0,
					(info->size_w + 2) * info->coeff), 1, ft_putchar_int);
		tputs(tgoto(tgetstr("UP", NULL), 0, info->nb_item), 1, ft_putchar_int);
	}
	else if (info->coeff > 0)
		tputs(tgoto(tgetstr("RI", NULL), 0,
					(info->size_w + 2) * info->coeff), 1, ft_putchar_int);
	if (info->count <= info->nb_item)
		info->size_last += 1;
	info->nb_item -= 1;
	info->count--;
}

void		longest_word(t_struct *info)
{
	t_lst	*ptr;

	ptr = info->node->head;
	info->size_w = 0;
	while (ptr)
	{
		if (ptr->len > info->size_w)
			info->size_w = ptr->len;
		ptr = ptr->next;
	}
	if (info->size_w + 2 < info->col)
		info->nb_col = info->col / (info->size_w + 2);
}
