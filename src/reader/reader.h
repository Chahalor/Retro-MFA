/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:21:10 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 16:50:03 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems   |----- */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>

/* -----| Globals   |----- */
# include "config.h"

/* -----| Internals |----- */
# include "_internal/_reader.h"

/* -----| Modules  |----- */
# include "mmanager.h"

/* ************************************************************************** */
/*                                 Typedefs                                   */
/* ************************************************************************** */

typedef enum e_extension	t_extension;

typedef struct s_image		t_image;
typedef struct s_data		t_data;

typedef struct s_bmp_header	t_bmp_header;

/* ************************************************************************** */
/*                                 Enums                                      */
/* ************************************************************************** */

enum e_extension
{
	EXT_NO_FILE,
	EXT_BMP,
	EXT_UNKNOWN
};

/* ************************************************************************** */
/*                                 Struct                                     */
/* ************************************************************************** */

#pragma pack(push, 1)
struct s_image
{
	uint16_t	width;
	uint16_t	height;
	size_t		nb_pixels;
	uint8_t		*pixels;	// data in rgb (3 oct per pixel)
};
#pragma pack(pop)

struct s_data
{
	t_image	files[MAX_HANDLED_IMAGE];
	size_t	nb_files;
};

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

t_data	*reader(
	const char *const restrict filename
);

int		write_file(
	void *const restrict data,
	t_extension type
);

#endif /* READER_H */