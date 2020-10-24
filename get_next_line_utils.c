/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:53:53 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/25 00:56:38 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	ans;

	ans = 0;
	while (s[ans])
		ans++;
	return (ans);
}

char	*ft_strdup(const char *s)
{
	size_t			s_len;
	char			*new_str;
	size_t			i;

	s_len = ft_strlen(s);
	if (!(new_str = (char*)malloc(s_len + 1)))
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[s_len] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	size_t			s_len;

	if (!(substr = malloc(len + 1)))
		return (NULL);
	*substr = '\0';
	if (start >= ft_strlen(s))
		return (substr);
	i = 0;
	s_len = ft_strlen(s);
	while (i < len && i < s_len)
	{
		substr[i] = *(s + start + i);
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char*)s;
	while (*str || !c)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	char			*ans;
	unsigned int	total_len;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = malloc(total_len + 1)))
		return (NULL);
	ans = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (ans);
}
