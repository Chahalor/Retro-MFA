/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:20:28 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/10 15:32:35 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# pragma once

/* ************************************************************************** */
/*                                 Configs                                    */
/* ************************************************************************** */

# define PNG_SIGNATURE "\x89PNG\r\n\x1a\n"
# define JPEG_SIGNATURE "\xFF\xD8\xFF"
# define BMP_SIGNATURE "BM"

# define unlikely(x) __builtin_expect(!!(x), 0)
# define likely(x)   __builtin_expect(!!(x), 1)

#endif /* CONFIG_H */