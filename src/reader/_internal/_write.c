/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _write.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 15:21:01 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region Header

/* -----| Systems   |----- */
	//...

/* -----| Internals |----- */
#include "_reader.h"

/* -----| Modules   |----- */
#include "reader.h"

#pragma endregion Header
#pragma region Fonctions

int	_write_file(
	void *const restrict data,
	t_extension type
)
{
	// const char	*filename = "tkt.bmp";
	// const int	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// const t_file	*file = (t_file *)data;
	
	// (void)type; // Suppress unused parameter warning
	// if (unlikely(fd < 0))
	// 	return (perror("Error opening file for writing"), -1);

	// write(fd, &file->data.header, sizeof(file->data.header));
	// write(fd, file->data.data, file->data.size);
	// close(fd);
	(void)data; // Suppress unused parameter warning
	(void)type; // Suppress unused parameter warning
	return (0);
}

#pragma endregion Fonctions