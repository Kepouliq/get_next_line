/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:55:19 by kepouliq          #+#    #+#             */
/*   Updated: 2024/06/25 15:16:57 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		s_len;
	char	*ptr_start;

	s_len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (s_len + 1));
	if (!ptr)
		return (NULL);
	ptr_start = ptr;
	while (*s)
	{
		*ptr = *s;
		ptr++;
		s++;
	}
	*ptr = '\0';
	return (ptr_start);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*start;
	size_t	len;

	len = nmemb * size;
	if (nmemb != 0 && len / nmemb != size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	start = ptr;
	while (len)
	{
		*start = 0;
		start++;
		len--;
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final_str;
	int		i;

	if (!s1)
		s1 = "";
	if (s2[0] == '\0')
		return (NULL);
	final_str = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!final_str)
		return (NULL);
	i = 0;
	while (*s1 && s1)
	{
			final_str[i++] = *s1;
			s1++;
	}
	while (*s2 && s2)
	{
			final_str[i++] = *s2;
			s2++;
	}
	final_str[i] = '\0';
	return (final_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;

	if (ft_strlen(s) <= 0)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s) - 1)
		return (ft_strdup(""));
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			sub[j++] = s[i];
		i++;
	}
	sub[j] = '\0';
	return (sub);
}
