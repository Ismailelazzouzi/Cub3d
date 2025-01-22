/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:25:41 by isel-azz          #+#    #+#             */
/*   Updated: 2025/01/22 11:25:44 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include "Libft/libft.h"
# include "get_next_line.h"

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	**maze;
	int		c[3];
	int		f[3];
	int		rows_num;
	int		column_num;
}	t_data;

#endif
