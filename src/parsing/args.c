/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/11 23:59:36 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region Header

/* -----| Systems   |----- */
# include <stdio.h>
# include <stdlib.h>

/* -----| Internals |----- */
#include "args.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

static inline void	show_usage(void)
{
	printf(BLUE "Usage" RESET ": retromfa {-h | --help | filename}\n");
}

__attribute__((noreturn)) static inline void	show_help(void)
{
	show_usage();
	printf(
		BLUE "Arguments:\n"
		RESET
		"  -h, --help\t\tShow this help message\n"
		"  filename\t\tSpecify the file to process\n"
		BLUE "Examples:\n"
		RESET
		"  ./program -h\n"
		"  ./program --help\n"
		"  ./program blue.mfa\n"
		YELLOW "Author: \n"
		RESET
		"  nduvoid  <" UNDERLINE "nduvoid@student.42mulhouse.fr" RESET ">\n"
		"  bcheronn <" UNDERLINE "bcheronn@student.42mulhouse.fr" RESET ">\n"
	);
	exit(0);
}

static inline int	parse_short_args(
	const char *args,
	t_args *const restrict result
)
{
	if (strncmp(args, "-h", 3) == 0)
		result->help = 1;
	else
		result->error = 1;
	return (1);
}

static inline int	parse_long_args(
	const char *args,
	t_args *const restrict result
)
{
	if (strncmp(args, "--help", 7) == 0)
		result->help = 1;
	else
		result->error = 1;
	return (1);
}


t_args	args_parser(
	const int argc,
	const char **argv
)
{
	t_args			result = {0};
	register int	i = 1;

	if (argc != 2)
	{
		result.error = 1;
		show_usage();
		return (result);
	}
	while (i < argc && !result.error && !result.help && !result.filename)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == '-')
				i += parse_long_args(argv[i], &result);
			else
				i += parse_short_args(argv[i], &result);
		}
		else
			result.filename = (char *)argv[i]; // Check for the four characters ".mfa" at the end of the filename
	}
	if (result.error)
		show_usage(); // Should not show usage when an error occurs
	else if (result.help)
		show_help();
	return (result);
}

#pragma endregion Fonctions