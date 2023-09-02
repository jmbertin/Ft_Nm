/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:56:58 by jbertin           #+#    #+#             */
/*   Updated: 2023/08/09 15:24:25 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/nm.h"

/**
 * Opens the file with the specified filename and checks its contents using the
 * ft_check function. If the file does not exist, it displays an error message.
 * @param	filename		The name of the file to process.
 * @param	multiple_files	An integer indicating if multiple files are being
 * 							processed. 1 for multiple files, 0 for a single file.
 * @return	Returns 1 if an error occurs, or the result of ft_check otherwise.
 */
static int	process_file(char *filename, int multiple_files)
{
	int	fd;
	int	ret;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
			ft_printf("nm %s: No such file\n", filename);
		return (1);
	}

	ret = ft_check(fd, filename, multiple_files);
	close(fd);
	return (ret);
}

/**
 * Main function to process files passed as command line arguments.
 * If no file is provided, it processes the default "a.out" file.
 * If multiple files are provided, it processes each file in order.
 * @param	argc	The number of command line arguments.
 * @param	argv	The array of command line arguments.
 * @return	Returns 0 if all files are successfully processed, or 1 if an error
 * 			occurs.
 */
int	main(int argc, char **argv)
{
	int	ret = 0;
	int	multiple_files = 0;

	if (argc < 2)
	{
		ret = process_file("a.out", multiple_files);
	}
	else
	{
		if (argc > 2)
			multiple_files = 1;
		for (int i = 1; i < argc; i++)
		{
			ret |= process_file(argv[i], multiple_files);
		}
	}
	return (ret);
}
