/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/12 09:45:52 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region Header

/* -----| Systems   |----- */
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* -----| Internals |----- */
	//...

/* -----| Modules   |----- */
#include "args.h"
#include "reader.h"

#pragma endregion Header
#pragma region Fonctions

__attribute__((destructor)) void	exiting(void)
{
	mm_destroy();
}

static inline t_image	read_next_image(
	const int fd,
	int *const end
)
{
	const uint8_t	signature[] = IMAGE_SIGNATURE;
	t_image	result;
	char	buffer[sizeof(signature)];
	int read_bytes;

	while ((read_bytes = read(fd, buffer, sizeof(buffer))) > (int)sizeof(buffer))
	{
		if (memcmp(buffer, signature, sizeof(signature)) == 0)
			break ;
		{
			lseek(fd, -6, SEEK_CUR);
			break ;
		}
	}
	if (read_bytes < 2)
	{
		*end = 1;
		return ((t_image){0});
	}
	read(fd, &result.width, sizeof(result.width));
	read(fd, &result.height, sizeof(result.height));
	lseek(fd, 2 + 16, SEEK_CUR); // Skip the next 2 bytes and the padding (reserved)
	result.nb_pixels = result.width * result.height;
	result.pixels = mm_alloc(result.nb_pixels * 3);
	if (unlikely(!result.pixels))
		return (perror("Memory allocation failed"), result);
	read(fd, result.pixels, result.nb_pixels * 3);
	return (result);
}

#pragma endregion Fonctions
#pragma region Main

int	main(int argc, const char **argv)
{
	const t_args	args = args_parser(argc, argv);
	const int		fd = open(args.filename, O_RDONLY);
	t_data			*data = NULL;
	register int	i = 0;
	int				end = 0;

	if (args.error)
		return (EXIT_FAILURE);
	else if (fd < 0)
		return (perror("Error opening file"), EXIT_FAILURE);

	data = mm_alloc(sizeof(t_data));
	if (unlikely(!data))
		return (perror("Memory allocation failed"), close(fd), EXIT_FAILURE);
	while (i < MAX_HANDLED_IMAGE && !end)
	{
		data->files[i] = read_next_image(fd, &end);
		++data->nb_files;
		i++;
	}
	printf("Read %zu images from file '%s'.\n", data->nb_files, args.filename);

	close(fd);
	return (0);
}

#pragma endregion Main