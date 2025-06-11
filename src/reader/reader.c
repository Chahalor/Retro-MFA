/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 11:38:57 by nduvoid          ###   ########.fr       */
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

static inline int	count_files(
	const char *const restrict filename,
	t_data *const restrict data
)
{
	const int	fd = open(filename, O_RDONLY);
	char		buffer[sizeof(PNG_SIGNATURE) - 1];
	int			bytes_read;

	if (unlikely(fd < 0))
		return (perror("Error opening file"), -1);
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		if (bytes_read < (int)sizeof(PNG_SIGNATURE) - 1)
			continue;
		if (memcmp(buffer, PNG_SIGNATURE, sizeof(PNG_SIGNATURE) - 1) == 0)
			++data->nb_png;
		else if (memcmp(buffer, JPEG_SIGNATURE, sizeof(JPEG_SIGNATURE) - 1) == 0)
			++data->nb_jpeg;
		else if (memcmp(buffer, BMP_SIGNATURE, sizeof(BMP_SIGNATURE) - 1) == 0)
			++data->nb_bmp;
	}
	data->count = data->nb_png + data->nb_jpeg + data->nb_bmp;
	return (close(fd), bytes_read < 0 ? -2 : 0);
}

static inline int	read_files(
	const char *const restrict filename,
	t_data *const restrict data
)
{
	const int	fd = open(filename, O_RDONLY);
	char		buffer[sizeof(BMP_SIGNATURE) - 1] = {0};
	int			bytes_read = -1;
	size_t		i = 0;

	if (unlikely(fd < 0))
		return (perror("reader: read_file(): Error opening file"), -1);
	data->files = (t_file **)mm_alloc(data->count * sizeof(t_file *));
	if (unlikely(!data->files))
		return (perror("reader: read_file(): Memory allocation failed"), close(fd), -2);
	while (i < data->count && (bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		if (memcmp(buffer, BMP_SIGNATURE, sizeof(buffer)) == 0)
		{
			lseek(fd, -(off_t)sizeof(buffer), SEEK_CUR);
			data->files[i++] = read_bmp(fd);
			printf("BMP file found, index: %zu (%p)\n", i - 1, data->files[i - 1]);
			break ;
		}
	}
	close(fd);
	return (bytes_read < 0 ? perror("reader: read_file(): Error reading file"), -3 : 0);
}

t_data	*reader(
	const char *const restrict filename
)
{
	t_data	*data = NULL;

	data = (t_data *)mm_alloc(sizeof(t_data));
	if (unlikely(!data))
		return (perror("reader(): Memory allocation failed"), NULL);
	else if (count_files(filename, data) < 0)
		return (perror("reader(): Failed to count files"), mm_free(data), NULL);
	else if (data->count == 0)
		return (perror("reader(): No files found"), mm_free(data), NULL);
	else if (read_files(filename, data) < 0)
		return (perror("reader(): Failed to read files"), mm_free(data), NULL);
	else
		return (data);
}

int	write_file(
	void *const restrict data,
	t_extension type
)
{
	return (_write_file(data, type));
}

#pragma endregion Fonctions