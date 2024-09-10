void		cmd_incantation(t_server *serv, int actual, char *buff)
{
	int		i;

	i = 0;
	(void)buff;
	if (!verif_lvl_tb(serv, actual))
	{
		if (serv->gfx.sock)
		{
			pie(serv->gfx.sock, serv->clients[actual].x,
					serv->clients[actual].y, 0);
			while (i < serv->connected)
				plv(serv->gfx.sock, &serv->clients[i++]);
			mct(serv->gfx.sock, serv);
		}
		write(serv->clients[actual].sock, "ko\n", 3);
		return ;
	}
	lvl_up_player(serv, actual, serv->clients[actual].x,
			serv->clients[actual].y);
}