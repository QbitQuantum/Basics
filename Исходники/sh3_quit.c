void	sh_quit(void)
{
	sh_reset_termios();
	set_winstruct(NULL, 1);
	tputs(tgetstr("ei", NULL), 0, tputchar);
	_Exit(0);
}