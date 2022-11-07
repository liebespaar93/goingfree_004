#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>
#include <fcntl.h>
#include <stdlib.h>

void ft_bitprintf(unsigned long data, int index)
{
	unsigned long bit;

	bit = data;
	if (index - 1)
		ft_bitprintf(data >> 1, index - 1);
	printf("%ld ", bit % 2);
}

void ft_terminal_printf(struct termios tty)
{
	printf("================ struct termios ================\n");
	printf("%20s\t%10lu\t", "tty.c_iflag", tty.c_iflag);
	ft_bitprintf(tty.c_iflag, 32);
	printf("\n");
	printf("%20s\t%10lu\t", "tty.c_oflag", tty.c_oflag);
	ft_bitprintf(tty.c_oflag, 32);
	printf("\n");
	printf("%20s\t%10lu\t", "tty.c_cflag", tty.c_cflag);
	ft_bitprintf(tty.c_cflag, 32);
	printf("\n");
	printf("%20s\t%10lu\t", "tty.c_lflag", tty.c_lflag);
	ft_bitprintf(tty.c_lflag, 32);
	printf("\n");
	printf("%20s\t%10lu\n", "tty.c_ispeed", tty.c_ispeed);
	printf("%20s\t%10lu\n", "tty.c_ospeed", tty.c_ospeed);
	printf("\n==============      c_cc      ==================\n");
	printf("%20s\t%d\n", "tty.c_cc[VEOF]", tty.c_cc[VEOF]);
	printf("%20s\t%d\n", "tty.c_cc[VEOL]", tty.c_cc[VEOL]);
	printf("%20s\t%d\n", "tty.c_cc[VEOL2]", tty.c_cc[VEOL2]);
	printf("%20s\t%d\n", "tty.c_cc[VERASE]", tty.c_cc[VERASE]);
	printf("%20s\t%d\n", "tty.c_cc[VWERASE]", tty.c_cc[VWERASE]);
	printf("%20s\t%d\n", "tty.c_cc[VKILL]", tty.c_cc[VKILL]);
	printf("%20s\t%d\n", "tty.c_cc[VREPRINT]", tty.c_cc[VREPRINT]);
	printf("%20s\t%d\n", "tty.c_cc[VINTR]", tty.c_cc[VINTR]);
	printf("%20s\t%d\n", "tty.c_cc[VQUIT]", tty.c_cc[VQUIT]);
	printf("%20s\t%d\n", "tty.c_cc[VSUSP]", tty.c_cc[VSUSP]);
	printf("%20s\t%d\n", "tty.c_cc[VDSUSP]", tty.c_cc[VDSUSP]);
	printf("%20s\t%d\n", "tty.c_cc[VSTART]", tty.c_cc[VSTART]);
	printf("%20s\t%d\n", "tty.c_cc[VSTOP]", tty.c_cc[VSTOP]);
	printf("%20s\t%d\n", "tty.c_cc[VLNEXT]", tty.c_cc[VLNEXT]);
	printf("%20s\t%d\n", "tty.c_cc[VDISCARD]", tty.c_cc[VDISCARD]);
	printf("%20s\t%d\n", "tty.c_cc[VMIN]", tty.c_cc[VMIN]);
	printf("%20s\t%d\n", "tty.c_cc[VTIME]", tty.c_cc[VTIME]);
	printf("%20s\t%d\n", "tty.c_cc[VSTATUS]", tty.c_cc[VSTATUS]);
};

void ft_bash_ttyset(struct termios *tty)
{
	if (!tty)
		return ;
	(*tty).c_iflag = BRKINT | ICRNL | IXON | IXANY | IMAXBEL | IUTF8;
	(*tty).c_oflag = OPOST | ONLCR;
	(*tty).c_cflag = CSIZE | CREAD | HUPCL;
	(*tty).c_lflag = ECHOKE | ECHOE | ECHOK | ECHO | ECHOCTL | ISIG | ICANON | IEXTEN | PENDIN;
	(*tty).c_ispeed = B38400;
	(*tty).c_ospeed = B38400;
	(*tty).c_cc[VEOF] = 4;
	(*tty).c_cc[VEOL] = 255;
	(*tty).c_cc[VEOL2] = 255;
	(*tty).c_cc[VERASE] = 127;
	(*tty).c_cc[VWERASE] = 23;
	(*tty).c_cc[VKILL] = 21;
	(*tty).c_cc[VREPRINT] = 18;
	(*tty).c_cc[VINTR] = 3;
	(*tty).c_cc[VQUIT] = 28;
	(*tty).c_cc[VSUSP] = 26;
	(*tty).c_cc[VDSUSP] = 25;
	(*tty).c_cc[VSTART] = 17;
	(*tty).c_cc[VSTOP] = 19;
	(*tty).c_cc[VLNEXT] = 22;
	(*tty).c_cc[VDISCARD] = 15;
	(*tty).c_cc[VMIN] = 1;
	(*tty).c_cc[VTIME] = 0;
	(*tty).c_cc[VSTATUS] = 20;
}
