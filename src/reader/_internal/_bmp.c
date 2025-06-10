/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/10 19:47:03 by nduvoid          ###   ########.fr       */
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

// t_file	*read_bmp(
// 	const int fd
// )
// {
// 	t_file	*file = NULL;
// 	char	buffer[8 * sizeof(int)];

// 	file = (t_file *)mm_alloc(sizeof(t_file) + sizeof(struct s_bmp) + sizeof(struct s_bmp_header));
// 	if (!file)
// 		return (NULL);
// 	file->type = EXT_BMP;
// 	file->data.bmp = (struct s_bmp *)((char *)file + sizeof(t_file));
// 	file->data.bmp->header = (struct s_bmp_header *)((char *)file + sizeof(t_file) + sizeof(struct s_bmp));
// 	file->data.bmp->header = "BM";
// 	read(fd, buffer, sizeof(buffer));
// 	file->data.bmp->header->bfSize = *(unsigned int *)(buffer + 2 * sizeof(int));
// 	file->data.bmp->header->bfReserved1 = *(unsigned short *)(buffer + 6 * sizeof(int));
// 	file->data.bmp->header->bfReserved2 = *(unsigned short *)(buffer + 7 * sizeof(int));
// 	file->data.bmp->header->bfOffBits = *(unsigned int *)(buffer + 8 * sizeof(int));
// 	file->data.bmp.data = mm_alloc(file->data.bmp->header->bfSize - file->data.bmp->header->bfOffBits);
// 	if (!file->data.bmp.data)
// 		return (mm_free(file), NULL);
// 	lseek(fd, file->data.bmp->header->bfOffBits, SEEK_SET);
// 	read(fd, file->data.bmp.data, file->data.bmp->header->bfSize - file->data.bmp->header->bfOffBits);
// 	return (file);
// }

t_file *read_bmp(const int fd) {
	t_file *file = mm_alloc(sizeof(t_file) + sizeof(t_bmp));
	if (!file)
		return (NULL);

	file->type = EXT_BMP;
	file->data.bmp = (t_bmp *)((char *)file + sizeof(t_file));

	// Lire l'en-tête BMP (14 octets)
	unsigned char header_buf[14];
	if (read(fd, header_buf, 14) != 14)
		return (mm_free(file), NULL);

	t_bmp_header *h = &file->data.bmp->header;

	h->bfType[0] = header_buf[0];
	h->bfType[1] = header_buf[1];

	if (h->bfType[0] != 'B' || h->bfType[1] != 'M')
		return (mm_free(file), NULL); // Pas un fichier BMP

	h->bfSize      = *(unsigned int *)(header_buf + 2);
	h->bfReserved1 = *(unsigned short *)(header_buf + 6);
	h->bfReserved2 = *(unsigned short *)(header_buf + 8);
	h->bfOffBits   = *(unsigned int *)(header_buf + 10);

	// Lire les données
	size_t data_size = h->bfSize - h->bfOffBits;
	void *data = mm_alloc(data_size);
	if (!data)
		return (mm_free(file), NULL);

	lseek(fd, h->bfOffBits, SEEK_SET);
	if (read(fd, data, data_size) != (ssize_t)data_size)
		return (mm_free(data), mm_free(file), NULL);

	file->data.bmp->data = data;
	file->data.bmp->size = data_size;

	return file;
}

#pragma endregion Fonctions