/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghoang <nghoang@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:18:17 by nghoang           #+#    #+#             */
/*   Updated: 2023/04/12 00:53:50 by nghoang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_read_save_left_str(int fd, char *left_str)
{
	char	*buf;
	int		rd_bytes;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	rd_bytes = 1;
	while (ft_strchr(left_str, '\n') == 0 && rd_bytes != 0)
	{
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buf);
	}
	free(buf);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*left_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str = ft_read_save_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	ret = ft_get_line(left_str);
	left_str = ft_cut_left_str(left_str);
	return (ret);
}
