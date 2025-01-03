/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:43:32 by ansoulai          #+#    #+#             */
/*   Updated: 2024/06/08 00:35:03 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_new_archive(char *archive)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (archive[i] && archive[i] != '\n')
		i++;
	if (!archive[i])
		return (NULL);
	str = (char *)ft_malloc(sizeof(char) * (ft_strlen(archive) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (archive[i])
		str[j++] = archive[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_get_line(char *archive)
{
	int		i;
	char	*str;

	i = 0;
	if (!archive[i])
		return (NULL);
	while (archive[i] && archive[i] != '\n')
		i++;
	str = (char *)ft_malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (archive[i] && archive[i] != '\n')
	{
		str[i] = archive[i];
		i++;
	}
	if (archive[i] == '\n')
	{
		str[i] = archive[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read_to_archive(int fd, char *archive)
{
	char	*buff;
	ssize_t	rd_bytes;

	buff = ft_malloc((size_t)BUFFER_SIZE * sizeof(char) + 1);
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(archive, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (NULL);
		buff[rd_bytes] = '\0';
		archive = ft_strjoin(archive, buff);
	}
	return (archive);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*archive;

	archive = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	archive = ft_read_to_archive(fd, archive);
	if (!archive)
		return (NULL);
	line = ft_get_line(archive);
	return (line);
}

// char    *get_next_line(int fd)
// {
//     char    *line;
//     char    *archive;

//     archive = NULL;
//     if (fd < 0 || BUFFER_SIZE <= 0)
//         return (NULL);
//     // Keep reading until we find a non-empty line
//     while (1)
//     {
//         archive = ft_read_to_archive(fd, archive);
//         if (!archive)
//             return (NULL);
//         line = ft_get_line(archive);
//         archive = ft_new_archive(archive);
//         // If line is not empty (not just newline or null), return it
//         if (line && line[0] != '\n' && line[0] != '\0')
//             return (line);
//         // If line is empty, free it and continue reading
//         if (line)
//             free(line);
//         // If we've reached end of file, return NULL
//         if (!archive)
//             return (NULL);
//     }
//     return (NULL);
// }

// int	main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("filename.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (0);
// 	line = get_next_line(fd);
// 	while(line != NULL)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);

// 	return (0);
// }