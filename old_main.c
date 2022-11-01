/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:21:08 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/01 07:57:55 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
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
#include <string.h>
// open
#include <fcntl.h>

// terminal con
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>


#include <readline/readline.h>
#include <readline/history.h>

#include <ft_env_tool.h>
#include <ft_export_tool.h>

int	main(int argc, const char *argv[], const char *envp[])
{
	(void)argc;
	(void)argv;
	// test global
	//** 꼭 들어온 값을 세팅해줄것
	global.origin_envp_ptr = envp;
	//** 주소를 저장하여 말록하지 않은것을 저장
	ft_global_init(envp);
	global.export_ptr = ft_export_init(envp);
	/* 
		처음 시작시 설정할 것들
		* _ 설정
		* SHLVL 설정 + 1
	*/
	char *SHLVL_UP = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	ft_putenv(ft_strjoin("SHLVL=", SHLVL_UP));
	free(SHLVL_UP);


	/* 
		터미널 설정
	*/

	char *modemdevice;
	int fd;
	modemdevice = ttyname(0);
	fd = open(modemdevice, O_RDWR | O_NOCTTY );
	if (fd <0)
	{
		printf("error ttyname get");
		exit(-1);
	}

	struct termios	old_termios;
	struct termios	new_termios;

	tcgetattr(fd, &old_termios);
	bzero(&new_termios, sizeof(new_termios));
	new_termios = old_termios;
	//new_termios.c_cflag = B38400 | CRTSCTS | CS8 | CLOCAL | CREAD;
//	new_termios.c_cc[VEOF] = 0;		/* Ctrl-d */
	new_termios.c_cc[VEOL] = 0;		/* '\0 ' */
	new_termios.c_cc[VEOL2] = 0;		/* '\0 ' */
	new_termios.c_cc[VERASE] = 0;	/* Ctrl-? del('\177') */
	new_termios.c_cc[VWERASE] = 0;	/* Ctrl-W */
	new_termios.c_cc[VKILL] = 0;		/* Ctrl-U */
	new_termios.c_cc[VREPRINT] = 0;	/* Ctrl-R */
//	new_termios.c_cc[VINTR] = 0;		/* Ctrl-C */
	new_termios.c_cc[VQUIT] = 0;		/* Ctrl-\\ */
	new_termios.c_cc[VSUSP] = 0;		/* Ctrl-Z */
	new_termios.c_cc[VDSUSP] = 0;	/* Ctrl-Y */
	new_termios.c_cc[VSTART] = 0;	/* Ctrl-Q */
	new_termios.c_cc[VSTOP] = 0;		/* Ctrl-S */
	new_termios.c_cc[VLNEXT] = 0;	/* Ctrl-V */
	new_termios.c_cc[VDISCARD] = 0;	/* Ctrl-O */
//	new_termios.c_cc[VMIN] = 0;		/* blocking read until 1 character arrives */
//	new_termios.c_cc[VTIME] = 0;		/* inter-character timer unused */
	new_termios.c_cc[VSTATUS] = 0;	/* Ctrl-T */
	tcflush(0,TCIFLUSH);
	tcsetattr(0, TCSANOW, &new_termios);

	// ternimal readline
	//
	while (1)
	{
		rl_on_new_line();

		printf("readline_echoing_p :%d\n", readline_echoing_p);
		printf("rl_readline_name :%s\n", rl_readline_name);
		printf("rl_basic_word_break_characters :%s\n", rl_basic_word_break_characters);
		printf("rl_completer_word_break_characters :%s\n", rl_completer_word_break_characters);
		printf("rl_completer_quote_characters :%s\n", rl_completer_quote_characters);
		printf("rl_already_prompted : %d\n", rl_already_prompted);
		printf("======\n");
		readline("minishell-0.3v : ");
		printf("prompt :%s\n", rl_prompt);
		printf("rl_line_buffer : %s\n", rl_line_buffer);
		printf("history_base :%d\n", history_base);
		printf("history_length :%d\n", history_length);
		printf("max_input_history : %d\n", max_input_history);
		printf("rl_terminal_name : %s\n", rl_terminal_name);
		printf("======\n");
		rl_display_match_list(completion_matches(rl_line_buffer, NULL));
		if (rl_completion_word_break_hook)
			printf("rl_completion_word_break_hook %s\n", (*rl_completion_word_break_hook)());

		printf("======\n");
		add_history(rl_line_buffer);
		rl_redisplay();
		if (rl_line_buffer[0] == 'q')
		{
			tcsetattr(0, TCSANOW, &old_termios);
			return (0);
		}
	}
	
	// test env_tool
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : env_tool \n");
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : ft_envargs \n");
	ft_envargs();
	printf("=====================\n");
	printf("ex : ft_putenv \n");
	//** ft_putenv 꼭 말록하여 넣어야함
	ft_putenv(ft_strdup("zz=2020"));
	printf("getenv zz (%p): %s\n", getenv("zz"), getenv("zz"));
	ft_putenv(ft_strdup("zz=2020"));
	printf("getenv zz (%p): %s\n", getenv("zz"), getenv("zz"));
	printf("=====================\n");
	printf("ex : ft_setenv \n");
	ft_setenv("zz", "4040", 0);
	printf("getenv zz (%p): %s\n", getenv("zz"), getenv("zz"));
	ft_setenv("zz", "6060", 1);
	printf("getenv zz (%p): %s\n", getenv("zz"), getenv("zz"));
	printf("=====================\n");
	printf("ex : ft_unsetenv \n");
	ft_unsetenv("zz");
	printf("getenv zz (%p):\n", getenv("zz"));
	
	// test export_tool
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : export_tool \n");
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : ft_export_init \n");
	ft_export_args();
	global.export_ptr = ft_export_init(envp);
	ft_export_args();
	printf("=====================\n");
	printf("ex : ft_export_find \n");
	printf("ft_export_find (%p): \n", ft_export_find("zz"));
	printf("=====================\n");
	printf("ex : ft_export_set \n");
	ft_export_set("zz");
	printf("1st ft_export_find (%p): %s\n", *ft_export_find("zz"), *ft_export_find("zz"));
	ft_export_set("zz");
	printf("2st ft_export_find (%p): %s\n", *ft_export_find("zz"), *ft_export_find("zz"));
	ft_export_set("zs");
	printf("3st ft_export_find (%p): %s\n", *ft_export_find("zs"), *ft_export_find("zs"));
	printf("=====================\n");
	printf("ex : ft_export_unset \n");
	ft_export_unset("zz");
	printf("ft_export_find (%p): \n", ft_export_find("zz"));
	printf("=====================\n");
	printf("ex : ft_export_args \n");
	ft_export_args();
	// test env
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : env \n");
	printf("=====================\n");
	printf("=====================\n");
	ft_putenv(ft_strdup("aaa=ss"));
	ft_export_set("aaa");
	ft_export_args();
	printf("================================\n");
	ft_envargs();
	printf("====sss=================\n");
	ft_putenv(ft_strdup("zzzzz=2"));
	ft_envargs();
	printf("================================\n");
	ft_env(1 ,(const char *[2]){"env", NULL});
	ft_env(3,(const char *[4]){"env", "test1=2", "test2=2", NULL});
	ft_envargs();
	ft_export_args();
	
	// test export
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : export \n");
	printf("=====================\n");
	printf("=====================\n");

	ft_export(1, (const char *[2]){"export", NULL});
	ft_export(3,(const char *[4]){"env", "test3=3", "test4=4", NULL});
	ft_export_args();

	// test unset
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : unset \n");
	printf("=====================\n");
	printf("=====================\n");

	ft_unset(1, (const char *[2]){"unset"});
	ft_unset(3, (const char *[4]){"env", "test3=3", "test4=4", NULL});
	ft_export_args();
	// test cd
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : cd \n");
	printf("=====================\n");
	printf("=====================\n");
	
	printf("ex : cd include \n");
	ft_cd(2, (const char *[2]){"cd", "include"});
	printf("%s=%s\n", "PWD", getenv("PWD"));
	printf("%s=%s\n", "OLDPWD", getenv("OLDPWD"));
	printf("ex : cd - \n");
	ft_cd(2, (const char *[2]){"cd", "-"});
	printf("%s=%s\n", "PWD", getenv("PWD"));
	printf("%s=%s\n", "OLDPWD", getenv("OLDPWD"));
	printf("ex : cd ~ \n");
	ft_cd(2, (const char *[2]){"cd", "~"});
	printf("%s=%s\n", "PWD", getenv("PWD"));
	printf("%s=%s\n", "OLDPWD", getenv("OLDPWD"));
	printf("ex : cd - \n");
	ft_cd(2, (const char *[2]){"cd", "-"});
	printf("%s=%s\n", "PWD", getenv("PWD"));
	printf("%s=%s\n", "OLDPWD", getenv("OLDPWD"));

	// test pwd
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : pwd \n");
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : pwd \n");
	ft_pwd();


	// test echo
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : echo \n");
	printf("=====================\n");
	printf("=====================\n");
	ft_echo(2, (const char *[3]){"echo", "-", NULL});
	ft_echo(3, (const char *[4]){"echo", "-n", "test echo write no -n", NULL});
	ft_echo(2, (const char *[3]){"echo", "test echo write", NULL});
	

	// test dir
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : dir \n");
	printf("=====================\n");
	printf("=====================\n");
	ft_dir_view("include");
	ft_dir_view("aa");
	ft_dir_view("..");

	printf("ft_readdir_get_file : %p\n ", ft_readdir_get_file("/Users/kyoulee/Documents/minishell/test1/test2","test.c"));
	

	// test file
	printf("=====================\n");
	printf("=====================\n");
	printf("ex : file \n");
	printf("=====================\n");
	printf("=====================\n");
	ft_file_view("include");
	ft_file_view("aa");
	ft_file_view("test.c");

	
	printf("ft_get_file : %s\n ", ft_get_file("env"));
	
	printf("ft_get_file : %s\n ", ft_get_file("ls"));
	
	printf("ft_get_file : %s\n ", ft_get_file("echo"));
	
	printf("ft_get_file : %s\n ", ft_get_file("test"));
	
	// test terminall

	// test exit
	// printf("=====================\n");
	// printf("=====================\n");
	// printf("ex : exit \n");
	// printf("=====================\n");
	// printf("=====================\n");
	// ft_exit(2, (const char *[2]){"exit", "-"});
	// ft_pwd();
	
	// test
	// int i = 0;
	// while (global.export_ptr[i])
	// {
	// 	printf("%s \==n", global.export_ptr[i]);
	// 	i++;
	// }
	// prin
	// ft_export_set("aa=");
	// ft_export_args();
	// ft_export_unset("aa");
	// ft_unsetenv("aa");
	// ft_export_set("aa");
	// ft_export_args();
	// ft_export_set("ba");
	// int i = 0;
	// while (global.export_ptr[i])
	// {
	// 	printf("%s \n", global.export_ptr[i]);
	// 	i++;
	// }
	// printf("ar: %s\n",argv[0]);
	// printf("ar: %s\n", getenv("_"));
	
	// test env
	// ft_setenv("na","22",1);
	// ft_setenv("1","22",1);
	// ft_putenv("ag=1");
	// ft_envargs();
	// ft_unsetenv("ag");
	// ft_envargs();
	// ft_envargs();

	// ft_cd(2, (const char *[2]){getenv("_"), "include"}, envp);
	// ft_pwd();
	//system("leaks a.out");	
	return 0;
}