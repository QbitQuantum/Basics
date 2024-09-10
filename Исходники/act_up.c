int	act_up(char *param, t_client *client, t_info *info)
{
  (void)param;
  move_up(client, client->direction, info);
  SEND(client->buf_write, OK);
  return (0);
}