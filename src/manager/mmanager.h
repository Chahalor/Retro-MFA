/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmanager.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:12:01 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 08:45:27 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMANAGER_H
# define MMANAGER_H

# pragma once

/* ************************************************************************** */
/*                                  Headers                                   */
/* ************************************************************************** */

/* -----| Systemes |----- */
# include <stdlib.h>
# include <unistd.h>

/* -----| Globals  |----- */
# include "config.h"

/* -----| Modules  |----- */
//...

/* ************************************************************************** */
/*                                  Prototypes                                */
/* ************************************************************************** */

// mmanager.c

void	*mm_alloc(
			const size_t size
			);

void	*mm_realloc(
			void *restrict ptr,
			const size_t nsize,
			const size_t osize
			);

void	mm_free(
			void *restrict ptr
			);

void	mm_destroy(void);

// fdmanager.c

int		fdm_open(
			const char *restrict path,
			const int flags,
			const int mode
			);

int		fdm_close(
			const int fd
			);

int		fdm_register(
			const int fd
			);

int		fdm_is_open(
			const int fd
			);

int		fdm_close_all(void);

#endif /* MMANAGER_H */