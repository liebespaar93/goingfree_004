#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <ft_env.h>  
#include <ft_global.h>
#include <ft_tool.h>
#include <ft_cd.h>
#include <ft_pwd.h>
#include <ft_export.h>
#include <ft_unset.h>
#include <ft_exit.h>
#include <ft_echo.h>
#include <ft_dir.h>
#include <ft_file.h>

#include <ft_env_tool.h>
#include <ft_export_tool.h>
#include <ft_terminal.h>

int main(void)
{
	struct termios	oldtty;
	struct termios	newtty;
	int 			fd;

	fd = open(ttyname(STDIN_FILENO), O_RDWR | O_NOCTTY );
	if (fd <0)
	{
		perror(ttyname(STDIN_FILENO));
		exit(-1);
	}
	tcgetattr(fd, &oldtty);
	ft_bzero(&newtty, sizeof(struct termios));
	ft_bash_ttyset(&newtty);
	tcsetattr(fd, TCSANOW, &newtty);
	ft_tty_loop();
	tcsetattr(fd, TCSANOW, &oldtty);
}