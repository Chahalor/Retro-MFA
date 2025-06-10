/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/10 19:36:01 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region Header

/* -----| Systems   |----- */
	//...

/* -----| Internals |----- */
	//...

/* -----| Modules   |----- */
#include "utils.h"

#pragma endregion Header
#pragma region Fonctions

/** */
__attribute__((always_inline, used, malloc)) inline void	*memdup(
	const void *const restrict src,
	size_t size
)
{
	char							*dup;
	const char *const	restrict	_src = (const char *)src;
	register size_t					i;

	dup = (char *)mm_alloc(size);
	if (__builtin_expect(!dup, unexpected))
		return (NULL);
	i = -1;
	while (++i < size)
		dup[i] = _src[i];
	return ((void *)dup);
}

#pragma endregion Fonctions