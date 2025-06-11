/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 11:40:45 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region Header

/* -----| Systems   |----- */
	//...

/* -----| Internals |----- */
	//...

/* -----| Modules   |----- */
#include "reader.h"

#pragma endregion Header
#pragma region Fonctions

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

t_file	*read_bmp(
	const int fd
)
{
	t_file				*file;
	struct s_bmp_header	header;
	void				*image_data;
	ssize_t				read_size;

	read_size = read(fd, &header, sizeof(header));
	if (read_size != sizeof(header))
		return (perror("read_bmp: Failed to read BMP header"), NULL);

	if (!(header.bfType[0] == 'B' && header.bfType[1] == 'M'))
		return (fprintf(stderr, "read_bmp: Invalid BMP signature\n"), NULL);

	size_t	data_size = header.bfSize - header.bfOffBits;
	image_data = mm_alloc(data_size);
	if (!image_data)
		return (perror("read_bmp: Failed to allocate memory for image data"), NULL);

	if (lseek(fd, header.bfOffBits, SEEK_SET) < 0)
		return (perror("read_bmp: Failed to seek to pixel data"), mm_free(image_data), NULL);

	read_size = read(fd, image_data, data_size);
	if (read_size != (ssize_t)data_size)	// cette condition est toujour fausse
		return (perror("read_bmp: Failed to read image data"), mm_free(image_data), NULL);

	file = mm_alloc(sizeof(t_file));
	if (!file)
		return (perror("read_bmp: Failed to allocate t_file"), mm_free(image_data), NULL);

	file->type = EXT_BMP;
	file->filename = NULL;
	file->data.header = header;
	file->data.size = data_size;
	file->data.data = image_data;

	return file;
}


#pragma endregion Fonctions