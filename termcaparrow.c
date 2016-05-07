/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 20:12:50 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/07 18:07:25 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"


static void	deal_with_left(t_struct *info)
{
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 68)
	{
		if (info->i[0] == 0 && info->i[1] != 1)
		{
			info->i[1] -= 1;
			info->i[0] = info->realcol;
		}
		else if (info->i[0] == 0 && info->i[1] == 1)
		{
			info->i[1] = info->size_last;
			info->i[0] = info->realcol;
		}
		else
			info->i[0] -= 1;
	}
}

static void	deal_with_right(t_struct *info)
{
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 67)
	{
		if (info->i[0] == info->realcol && info->i[1] != info->size_last)
		{
			info->i[0] = 0;
			info->i[1] += 1;
		}
		else if (info->i[0] == info->realcol && info->i[1] == info->size_last)
		{
			info->i[0] = 0;
			info->i[1] = 1;
		}
		else
			info->i[0] += 1;
	}
}

static void	deal_with_down(t_struct *info)
{
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 66 &&
			info->i[1] <= info->j)
	{
		if (info->i[1] == info->size_last && info->i[0] == info->realcol)
		{
			info->i[0] = 0;
			info->i[1] = 1;
		}
		else if (info->i[1] == info->j)
		{
			info->i[0] += 1;
			info->i[1] = 1;
		}
		else
			info->i[1] += 1;
	}
}

static void	deal_with_up(t_struct *info)
{
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 65 &&
			info->i[1] > 0)
	{
		if (info->i[1] == 1 && info->i[0] != 0)
		{
			info->i[1] = info->j;
			info->i[0] -= 1;
		}
		else if (info->i[1] == 1 && info->i[0] == 0)
		{
			info->i[1] = info->size_last;
			info->i[0] = info->realcol;
		}
		else
			info->i[1] -= 1;
	}
}

void		deal_with_arrow(t_struct *info)
{
	deal_with_up(info);
	deal_with_down(info);
	deal_with_left(info);
	deal_with_right(info);
}
