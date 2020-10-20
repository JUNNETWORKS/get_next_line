/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 23:43:27 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/21 02:16:37 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define EOF (-1)
# define BUFFER_SIZE (32)

typedef struct		s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;

int	get_next_line(int fd, char **line);

char	*ft_strdup(const char *s);
t_list	*ft_lstnew(char *str);
int	ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
size_t	ft_strlen(const char *s);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstadd_str_back(t_list **lst, char *str);
void	ft_lstclear(t_list **lst);

#endif
