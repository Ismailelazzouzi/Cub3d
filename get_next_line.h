/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <isel-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 05:41:46 by isel-azz          #+#    #+#             */
/*   Updated: 2023/12/22 05:31:01 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*nextcall_prep(char *retholder, char *holder);
char	*extract_line(char *holder);
char	*generate_line(char **holder_ptr, int fd);
char	*join_strs(char *s1, char *s2);
int		found_newline(char *holder);
#endif
