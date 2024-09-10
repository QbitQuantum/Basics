/** 
  * Write udhcpd.conf
  * @ipforward : NULL if we want a simple config, otherwise include dns info etc...
  */
static int write_udhcpd_conf(struct ipforward_data *ipforward, struct mode_list_elem *data)
{
  FILE *conffile;
  char *ip, *interface;
  char *ipstart, *ipend;
  int dot = 0, i = 0, test;
  struct stat st;

  /* /tmp is often tmpfs, so we avoid writing to flash */
  conffile = fopen("/tmp/udhcpd.conf", "w");
  if(conffile == NULL)
  {
	log_debug("Error creating /etc/udhcpd.conf!\n");
	return(1);
  }

  /* generate start and end ip based on the setting */
  ip = get_network_ip();
  if(ip == NULL)
  {
	ip = strdup("192.168.2.15");
  }
  ipstart = malloc(sizeof(char)*15);
  ipend = malloc(sizeof(char)*15);
  while(i < 15)
  {
        if(dot < 3)
        {
                if(ip[i] == '.')
                        dot ++;
                ipstart[i] = ip[i];
                ipend[i] = ip[i];
        }
        else
        {
                ipstart[i] = '\0';
                ipend[i] = '\0';
                break;
        }
        i++;
  }
  strcat(ipstart,"1");
  strcat(ipend, "10");

  interface = get_interface(data);
  /* print all data in the file */
  fprintf(conffile, "start\t%s\n", ipstart);
  fprintf(conffile, "end\t%s\n", ipend);
  fprintf(conffile, "interface\t%s\n", interface);
  fprintf(conffile, "option\tsubnet\t255.255.255.0\n");
  if(ipforward != NULL)
  {
	if(!ipforward->dns1 || !ipforward->dns2)
	{
		log_debug("No dns info!");
	}
	else
		fprintf(conffile, "opt\tdns\t%s %s\n", ipforward->dns1, ipforward->dns2);
	fprintf(conffile, "opt\trouter\t%s\n", ip);
  }

  free(ipstart);
  free(ipend);
  free(ip);
  free(interface);
  fclose(conffile);
  log_debug("/etc/udhcpd.conf written.\n");

  /* check if it is a symlink, if not remove and link, create the link if missing */
  test = stat("/etc/udhcpd.conf", &st);
  /* if stat fails there is no file or link */
  if(test == -1)
	goto link;
  /* if it is not a link we remove it, else we expect the right link to be there */
  if((st.st_mode & S_IFMT) != S_IFLNK)
  {
	unlink("/etc/udhcpd.conf");
  }
  else
	goto end;

link:
  symlink("/tmp/udhcpd.conf", "/etc/udhcpd.conf");

end:

  return(0);
}