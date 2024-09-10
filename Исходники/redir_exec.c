int		heredoc(t_group *grp, t_redir *curr)
{
	int		fd;

	TERM(other_read) = true;
	set_shell((~ICANON & ~ECHO));
	fd = open(TMP_FROM, O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (grp->exit[1] == false)
	{
		TERM(cmd_line) = ft_strdup("");
		show_prompt(grp, "heredoc> ", 9, "\033[1;34m");
		read_cmd(grp, 0);
		if (ft_strcmp(TERM(cmd_line), curr->name) == 0)
			break ;
		ft_putendl_fd(TERM(cmd_line), fd);
		REMOVE(&TERM(cmd_line));
	}
	TERM(curs_pos) = 0;
	TERM(cmd_size) = 0;
	REMOVE(&TERM(cmd_line));
	TERM(other_read) = false;
	reset_shell();
	return (true);
}