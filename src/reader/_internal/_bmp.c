/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 15:23:10 by nduvoid          ###   ########.fr       */
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

// static inline t_file	*_read(
// 	const int fd,
// 	t_file *file
// )
// {
// 	unsigned char	buff_header[12];

// 	read(fd, buff_header + 2, 12);
// 	file->type = EXT_BMP;
// 	file->header.bfType[0] = buff_header[0];
// 	file->header.bfType[1] = buff_header[1];
// 	file->header.bfSize = *(unsigned int *)(buff_header + 2);
// 	file->header.bfReserved1 = *(unsigned short *)(buff_header + 6);
// 	file->header.bfReserved2 = *(unsigned short *)(buff_header + 8);
// 	file->header.bfOffBits = *(unsigned int *)(buff_header + 10);
// 	read(fd, &file->header + 1, file->header.bfSize - sizeof(t_bmp_header));
// 	return (file);
// }

// t_file	*read_bmp(
// 	const int fd
// )
// {
// 	t_file			*file;
// 	t_bmp_header	header;

// 	file = mm_alloc(sizeof(t_file));
// 	if (unlikely(!file))
// 		return (NULL);

// 	while (read(fd, header.bfType, 2) == 2 && !file)
// 		if (strncmp((char *)header.bfType, "BM", 2) != 0)
// 			file = _read(fd, file);
// 	return (file);
// }

static inline t_file *_read(const int fd, t_file *file)
{
	unsigned char	buff_header[14]; // 14 = taille du t_bmp_header

	if (read(fd, buff_header, 14) != 14)
		return (NULL);

	file->header.bfType[0] = buff_header[0];
	file->header.bfType[1] = buff_header[1];
	file->header.bfSize = *(unsigned int *)(buff_header + 2);
	file->header.bfReserved1 = *(unsigned short *)(buff_header + 6);
	file->header.bfReserved2 = *(unsigned short *)(buff_header + 8);
	file->header.bfOffBits = *(unsigned int *)(buff_header + 10);

	size_t remaining = file->header.bfSize - 14;
	if (remaining > 0)
		read(fd, ((unsigned char *)&file->header) + 14, remaining);
	return (file);
}

t_file *read_bmp(const int fd)
{
	unsigned char	magic[2];

	if (read(fd, magic, 2) != 2)
		return (NULL);
	if (magic[0] != 'B' || magic[1] != 'M')
		return (NULL);

	// On remet les deux octets lus en tête pour les passer à _read
	t_file *file = mm_alloc(sizeof(t_file));
	if (unlikely(!file))
		return (NULL);
	file->header.bfType[0] = magic[0];
	file->header.bfType[1] = magic[1];

	// Le fd a déjà avancé de 2, _read doit s'adapter
	if (!_read(fd, file))
	{
		free(file);
		return (NULL);
	}
	return (file);
}



#pragma endregion Fonctions