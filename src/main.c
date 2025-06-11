/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 10:32:31 by nduvoid          ###   ########.fr       */
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

#pragma endregion Fonctions
#pragma region Main

int	main(int argc, const char **argv)
{
	const t_args	args = args_parser(argc, argv);
	t_data			*data = NULL;

	if (args.error)
		return (EXIT_FAILURE);
	
	data = reader(args.filename);
	if (unlikely(!data))
		return (perror("Error reading file"), EXIT_FAILURE);
	printf(
		"Files found inside " ITALIC "%s" RESET ": %zu\n"
		"  PNG: %zu\n"
		"  JPEG: %zu\n"
		"  BMP: %zu\n",
		args.filename, data->count, data->nb_png, data->nb_jpeg, data->nb_bmp
	);
	size_t	i = -1;
	while (++i < data->count)
	{
		if (likely(data->files[i]))
		{
			printf("file.type: %d\n", data->files[i]->type);
			write_file((void *)data->files[i], data->files[i]->type);
		}
	}
	
	// display_logic, could replace the create file logic

	return (0);
}

#pragma endregion Main