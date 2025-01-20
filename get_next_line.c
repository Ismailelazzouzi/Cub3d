/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <isel-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 05:38:34 by isel-azz          #+#    #+#             */
/*   Updated: 2023/12/22 05:34:16 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char	*generate_line(char **holder_ptr, int fd)
{
	char	*hold;
	int		readed;

	readed = 1;
	hold = malloc((size_t)BUFFER_SIZE + 1);
	if (!hold)
		return (free(*holder_ptr), *holder_ptr = NULL, NULL);
	while (found_newline(*holder_ptr) != 0 && readed > 0)
	{
		readed = read(fd, hold, BUFFER_SIZE);
		if (readed <= 0)
			break ;
		hold[readed] = '\0';
		*holder_ptr = join_strs(*holder_ptr, hold);
		if (!*holder_ptr)
			return (free(hold), hold = NULL, *holder_ptr = NULL, NULL);
	}
	if (!holder_ptr[0])
		return (free(hold), hold = NULL, NULL);
	return (free(hold), hold = NULL, *holder_ptr);
}

char	*extract_line(char *holder)
{
	char	*ret;
	int		i;
	int		j;

	if (!holder)
		return (NULL);
	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	if (holder[i] != '\0')
		i++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	j = i;
	i = 0;
	while (i < j)
	{
		ret[i] = holder[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*nextcall_prep(char *retholder, char *holder)
{
	int	i;
	int	j;

	if (!holder)
		return (NULL);
	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	if (holder[i] == '\n')
		i++;
	j = 0;
	while (holder[i])
	{
		retholder[j] = holder[i];
		i++;
		j++;
	}
	if (j == 0)
	{
		free(holder);
		return (0);
	}
	retholder[j] = '\0';
	return (retholder);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*line;

	line = NULL;
	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0 || read(fd, "", 0) < 0
		|| BUFFER_SIZE > INT_MAX)
		return (free(holder), holder = NULL, NULL);
	holder = generate_line(&holder, fd);
	if (!holder)
		return (free(line), NULL);
	line = extract_line(holder);
	if (!line)
		return (free(holder), holder = NULL, NULL);
	holder = nextcall_prep(holder, holder);
	return (line);
}
