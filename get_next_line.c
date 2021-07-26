#include "get_next_line.h"

t_list			*ft_lstnew(int fd)
{
	t_list *node;

	if (!(node = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	node->fd = fd;
	node->contents = NULL;
	node->next = NULL;
	return (node);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*head;
	t_list			*backup_buf;
	char			*buf;
	ssize_t			read_size;

	if (fd < 0 || line == NULL)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	backup_buf = find_buf(&head, fd);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (backup_buf->contents == NULL)
			backup_buf->contents = ft_strdup(buf);
		else
			backup_buf->contents = ft_strjoin(backup_buf->contents, buf);
		if (ft_strchr(backup_buf->contents, '\n'))
			break ;
	}
	free(buf);
	if (read_size >= 0)
		return (check_line(&head, fd, line));
	ft_lstdelone(&head, fd);
	return (-1);
}
