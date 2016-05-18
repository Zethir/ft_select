/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:50:27 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/18 18:31:01 by cboussau         ###   ########.fr       */
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
	size_t			line;
	int				index;
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
	size_t			size_last;
	size_t			col;
	size_t			row;
	size_t			nb_col;
	size_t			nb_item;
	size_t			coeff;
	size_t			count;
	size_t			realcol;
	size_t			len;
	size_t			delkey;
	size_t			size_w;
	int				fd;
	char			buff[BUFF_SIZE];
	struct termios	term;
	struct s_intel	*node;
}					t_struct;

t_intel				*init_lst(char **argv);
t_intel				*add_elem(t_intel *node, char *argv);
t_struct			*init_struct(char **argv);
t_struct			*stock_struct(t_struct *info, int i);
char				*deal_with_term(t_struct *info);
char				*do_select(char **argv, int id);
void				push_node(t_lst *node, t_lst **head);
void				clean_lst(t_struct *info);
void				print_opt(t_lst *ptr, t_struct *info);
void				deal_with_arrow(t_struct *info);
void				deal_with_col(t_struct *info);
void				longest_word(t_struct *info);
void				print_lst(t_struct *info);
void				init_ptr(t_struct *info);
void				del_elem_from_list(t_struct *info);
void				left_arrow(t_struct *info, t_lst *ptr);
void				right_arrow(t_struct *info, t_lst *ptr);
void				check_size(t_struct *info);
void				win_size(int id);
void				ft_signal(int id);
void				sigcont(int id);
void				sigtstp(int id);
void				sigint(int id);
void				start_end(t_struct *info);
void				free_lst(t_struct *info);
int					init_term(t_struct *info);
int					reset_term(t_struct *info);

#endif
