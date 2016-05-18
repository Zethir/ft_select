/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:58:00 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/18 18:01:24 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		delete_elem(t_lst *ptr, t_struct *info)
{
	t_lst	*del;

	del = ptr;
	if (del == info->node->tail)
		info->node->tail = del->prev;
	if (del == info->node->head)
	{
		if (!del->next)
		{
			tputs(tgetstr("ue", NULL), 0, ft_putchar_int);
			clean_lst(info);
			ft_putendl_fd("There is no elements in this list anymore.", 2);
			free_lst(info);
			reset_term(info);
			exit(-1);
		}
		info->node->head = del->next;
	}
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del);
	info->node->length -= 1;
}

void			del_elem_from_list(t_struct *info)
{
	t_lst	*ptr;

	ptr = info->node->head;
	while (ptr->line != 1)
		ptr = ptr->next;
	ptr->line = 0;
	if (ptr->next)
		ptr->next->line = 1;
	else if (ptr->prev)
		ptr->prev->line = 1;
	delete_elem(ptr, info);
}

static t_lst	*init_elem(char *argv)
{
	t_lst *ptr;

	if (!(ptr = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	ptr->name = ft_strdup(argv);
	ptr->select = 0;
	ptr->save = NULL;
	ptr->len = ft_strlen(ptr->name);
	ptr->index += 1;
	ptr->next = NULL;
	return (ptr);
}

t_intel			*add_elem(t_intel *node, char *argv)
{
	t_lst	*ptr;

	if (node != NULL)
	{
		ptr = init_elem(argv);
		if (node->tail == NULL)
		{
			ptr->prev = NULL;
			node->head = ptr;
			node->tail = ptr;
		}
		else
		{
			node->tail->next = ptr;
			ptr->prev = node->tail;
			node->tail = ptr;
		}
		node->length++;
	}
	return (node);
}

t_intel			*init_lst(char **argv)
{
	t_intel	*node;
	size_t	i;

	i = 1;
	if (!(node = (t_intel *)malloc(sizeof(t_intel))))
		return (NULL);
	node->length = 0;
	node->head = NULL;
	node->tail = NULL;
	while (argv[i])
	{
		node = add_elem(node, argv[i]);
		i++;
	}
	return (node);
}
