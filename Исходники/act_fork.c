int	act_fork(char *param, t_client *client, t_info *info)
{
  (void)param;
  (void)info;
  info->zone[client->x][client->y].nb_egg++;
  SEND(client->buf_write, OK);
  return (0);
}