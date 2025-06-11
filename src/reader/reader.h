/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:21:10 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 11:26:58 by nduvoid          ###   ########.fr       */
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

typedef struct s_file		t_file;
typedef struct s_data		t_data;

typedef struct s_bmp	t_bmp;
typedef struct s_jpeg	t_jpeg;

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

struct s_bmp_header
{
	unsigned char	bfType[2];		// "BM"
	unsigned int	bfSize;			// Size of the file in bytes
	unsigned short	bfReserved1;	// Reserved, must be 0
	unsigned short	bfReserved2;	// Reserved, must be 0
	unsigned int	bfOffBits;		// Offset to the pixel data
};

struct s_bmp
{
	struct s_bmp_header		header;
	void					*data;
	size_t					size;
};

struct s_file
{
	t_extension		type;
	t_bmp			data;
	char			*filename;
};

struct s_data
{
	t_file	**files;
	size_t	count;
	size_t	nb_png;
	size_t	nb_jpeg;
	size_t	nb_bmp;
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