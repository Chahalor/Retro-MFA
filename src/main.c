/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/10 15:20:59 by nduvoid          ###   ########.fr       */
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

#pragma endregion Header
#pragma region Fonctions

/**
 * @brief Searche the array target in the array src.
 */
void	*ft_memchr(
	const void *src,
	const void *target,
	const size_t len_src,
	const size_t len_target
)
{
	void			*result;
	register size_t	i;
	register size_t	j;

	result = NULL;
	i = -1;
	while (++i < len_src)
	{
		if (*(unsigned char *)(src + i) == *(unsigned char *)target)
		{
			j = 0;
			while (j < len_target && i + j < len_src
				&& *(unsigned char *)(src + i + j) == *(unsigned char *)(target + j))
			{
				j++;
			}
			if (j == len_target)
			{
				result = (void *)(src + i);
				return (result);
			}
		}
	}
	return (result);
}

#pragma endregion Fonctions
#pragma region Main

int	main(int argc, const char **argv)
{
	const t_args	args = args_parser(argc, argv);

	if (args.error)
		return (EXIT_FAILURE);
	
	return (0);
}

#pragma endregion Main