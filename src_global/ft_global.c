
#include <ft_global.h>
#include <stdlib.h>

void	ft_global_init(const char **envp)
{
	char	**tmp;
	int		i;


	tmp = (char **)envp;
	while (*tmp++)
		;
	global.export_ptr = malloc(sizeof(char **));
	global.origin_envp = malloc(sizeof(char *) * (tmp - (char **)envp));
	if (!global.export_ptr || !global.origin_envp)
		return ;
	tmp = (char **)envp;
	i = 0;
	while (*tmp)
		global.origin_envp[i++] = *tmp++;
	global.origin_envp[i] = NULL;
}

int	ft_find_origin_envp(void **ptr)
{
	char	**tmp;
	
	tmp = (char **)global.origin_envp;
	while (*tmp)
	{
		if (*tmp == *ptr)
			return (1);
		tmp++;
	}
	return (0);
}