int show_whitelist_ip(void)
{
  cmd_hdr *cmd;
  get_wl_ip_key_obj *req;
  get_wl_ip_key_obj next;
  get_wl_ip_acl_obj *wl_obj;
  src_dest_acl_obj *acl_obj;
  time_t cur_time;
  double delta_time;
  char buf[1024];
  char *pbuf = buf;
  char src_ip[15];
  char dst_ip[15];
  char acl_id[15];
  int secs_left;
  int i;
  int ctr = 1;
  int buf_len;
  int more = TRUE;
  int is_first = TRUE;
  int ret;

  memset(&next, 0, sizeof(next));

  while (more)
  {
    cmd = (cmd_hdr *)pbuf;

    memset(cmd, 0, sizeof(cmd_hdr));
    cmd->type = CMD_REQUEST;
    cmd->cmd_id = CMD_GET_WHITELIST_IP;
    cmd++;

    req = (get_wl_ip_key_obj *)cmd;
    *req = next;
    req++;

    buf_len = sizeof(buf);
    ret = send_req((char *)pbuf, ((char *)req - buf), (char *)buf, &buf_len);
    if (ret)
    {
      fprintf(stdout, "Daemon is down.\n");
      break;
    }

    cmd = (cmd_hdr *)buf;
    if ((cmd->type != CMD_RESPONSE) || (cmd->cmd_id != CMD_GET_WHITELIST_IP))
    {
      fprintf(stdout, " Unexpected response. Skipping.\n");
      break;
    }

    cmd++;
    wl_obj = (get_wl_ip_acl_obj *)cmd;

    if (is_first)
    {
      fprintf(stdout, "Whitelisted Source-Destination IP Pair\n");
      fprintf(stdout, "======================================\n");
      fprintf(stdout, "ID  SourceIP   DestinationIP   Seconds Left  Age\n\n");

      if (!wl_obj->n_acl)
      {
        fprintf(stdout, " No whitelisted source-destination IPs.\n");
        break;
      }

      is_first = FALSE;
    }

    if (!wl_obj->n_acl)
    {
      break;
    }

    cur_time = time(NULL);

    acl_obj = (src_dest_acl_obj *)(wl_obj + 1);
    for (i = 0; i < wl_obj->n_acl; i++, acl_obj++, ctr++)
    {
      snprintf(src_ip, sizeof(src_ip), "%d.%d.%d.%d",
               (acl_obj->src >> 24) & 0xFF,
               (acl_obj->src >> 16) & 0xFF,
               (acl_obj->src >> 8) & 0xFF,
               acl_obj->src & 0xFF);

      snprintf(dst_ip, sizeof(dst_ip), "%d.%d.%d.%d",
               (acl_obj->dst >> 24) & 0xFF,
               (acl_obj->dst >> 16) & 0xFF,
               (acl_obj->dst >> 8) & 0xFF,
               acl_obj->dst & 0xFF);

      snprintf(acl_id, sizeof(acl_id), "[%d]", ctr);

      delta_time = difftime(cur_time, (time_t)acl_obj->created_at);
      secs_left = acl_obj->age - (int)delta_time;

      fprintf(stdout, "%-5s %-16s %-16s %-5d %lu\n",
              acl_id, src_ip, dst_ip, secs_left, acl_obj->age);

      next.src = acl_obj->src;
      next.dst = acl_obj->dst;
    }

    // more = FALSE;
  }

  fprintf(stdout, "\n");

  ret = RET_OK;

  return(ret);
}