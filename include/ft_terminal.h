/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:16:36 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/07 07:56:50 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERMINAL_H
# define FT_TERMINAL_H

# define ERROR_SYNTAX 1

# include <termios.h>

typedef struct s_cmd
{
	int		argc;
	char	**argv;
}	t_cmd;



void ft_terminal_printf(struct termios tty);
void ft_bash_ttyset(struct termios *tty);
void ft_cmd(const char *history);
void ft_tty_loop();





int	ft_cmd_init(t_cmd *cmd, char *history_str);

#endif