/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _reader.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:33:36 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/10 19:31:55 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _READER_H
# define _READER_H

# pragma once

/* ************************************************************************** */
/*                                 Headers                                    */
/* ************************************************************************** */

/* -----| Systems   |----- */
	//...

/* -----| Globals   |----- */
# include "config.h"

/* -----| Internals |----- */
# include "reader.h"

/* -----| Modules  |----- */
	//...

/* ************************************************************************** */
/*                                 Typedefs                                   */
/* ************************************************************************** */

//...

/* ************************************************************************** */
/*                                 Enums                                      */
/* ************************************************************************** */

//...

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

struct s_jpeg_header
{
	unsigned char	soi[2];		// Start of Image marker (0xFFD8)
	unsigned char	app0[2];	// Application marker (0xFFE0)
	unsigned short	length;		// Length of the APP0 segment
	char			id[5];		// "JFIF\0"
	unsigned char	version[2];	// JFIF version
	unsigned char	reserved;	// Reserved byte
	unsigned char	unit;		// Density unit
	unsigned short	xDensity;	// Horizontal pixel density
	unsigned short	yDensity;	// Vertical pixel density
	unsigned char	xThumbnail; // Thumbnail width
	unsigned char	yThumbnail; // Thumbnail height
};

struct s_jpeg
{
	struct s_jpeg_header	header;
	void					*data;
	size_t					size;
};

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

t_file	*_read_jpeg(
	const int fd
);

t_file	*_read_bmp(
	const int fd
);

#endif /* _READER_H */