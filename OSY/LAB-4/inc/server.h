/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:49:55 by kostya            #+#    #+#             */
/*   Updated: 2021/12/12 23:03:00 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

typedef struct	s_server
{
	int			socket;
	int			client;
}				t_server;

// typedef struct	s_button_checker
// {
// 	e_button		button;
// 	pthread_mutex_t	mutex;
// 	int				socket;
// }				t_button_checker;

// # define INDEX_HTML		"html/index.html"
# ifndef INDEX_HTML
#  define INDEX_HTML		"html/orig.html"
# endif

#endif
