/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:20:28 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 17:00:33 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# pragma once

/* ************************************************************************** */
/*                                 Configs                                    */
/* ************************************************************************** */

# define IMAGE_SIGNATURE 0x0610

# define unlikely(x) __builtin_expect(!!(x), 0)
# define likely(x)   __builtin_expect(!!(x), 1)

# define MAX_HANDLED_IMAGE 32

#endif /* CONFIG_H */