/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nduvoid <nduvoid@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:44:25 by nduvoid           #+#    #+#             */
/*   Updated: 2025/06/10 15:10:01 by nduvoid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region Header

/* -----| Systems   |----- */
	//...

/* -----| Internals |----- */
#include "args.h"

/* -----| Modules   |----- */
	//...

#pragma endregion Header
#pragma region Fonctions

static inline void	show_usage(void)
{
	printf(BLUE "Usage" RESET ": ./program [options] [filename]\n");
}

static inline void	show_help(void)
{
	show_usage();
	printf("TODO: Implement help message\n");
}

static inline int	parse_short_args(
	const char *args,
	t_args *const restrict result
)
{
	if (strncmp(args, "-h", 2))
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
	if (strncmp(args, "--help", 6) == 0)
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
	register int	i = 0;


	if (argc < 2)
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
				i += parse_long_args(argv[i] + 2, &result);
			else
				i += parse_short_args(argv[i] + 1, &result);
		}
		else
			result.filename = (char *)argv[i];
	}
	if (result.error)
		show_usage();
	return (result);
}

#pragma endregion Fonctions