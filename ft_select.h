/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:50:27 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/07 17:59:29 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

typedef struct		s_lst
{
	char			*name;
	size_t			select;
	char			*save;
	size_t			len;
	struct s_lst	*prev;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_intel
{
	size_t			length;
	struct s_lst	*tail;
	struct s_lst	*head;
}					t_intel;

typedef struct		s_struct
{
	size_t			i[2];
	size_t			j;
	size_t			k;
	size_t			index[2];
	size_t			size_last;
	size_t			col;
	size_t			row;
	size_t			nb_col;
	size_t			nb_item;
	size_t			coeff;
	size_t			realcol;
	char			buff[BUFF_SIZE];
}					t_struct;

t_intel				*init_lst(char **argv);
t_intel				*add_elem(t_intel *node, char *argv);
char				*deal_with_term(t_intel *node, t_struct *info);
void				push_node(t_lst *node, t_lst **head);
void				print_select(t_intel *node);
void				clean_lst();
void				print_opt(t_intel *node, t_lst *ptr, t_struct *info);
void				deal_with_arrow(t_struct *info);
void				deal_with_col(t_intel *node, t_struct *info);
void				longest_word(t_intel *node, t_struct *info);
void				print_lst(t_intel *node, t_struct *info);
void				win_size();
void				ft_signal(t_intel *node, t_struct *info);
int					init_term(void);
int					reset_term(void);

#endif
