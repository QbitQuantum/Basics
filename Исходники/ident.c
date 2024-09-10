/********************************************************************
 * Function : id_lookup_username
 * Created  : 97/03/31
 * Author   : Joachim Pileborg
 * E-Mail   : [email protected]
 *
 * Try to get a username from a user.
 */
static char *id_lookup_username(struct sockaddr_in sa)
{
  static char        username[256];
  char               string[256];
  struct hostent    *hent;
  struct sockaddr_in saddr;
  int                sock;

  extern int port;

  sprintf(string, "%d, %d\r\n", ntohs(sa.sin_port), port);

  if (!(hent = gethostbyaddr((char *) &sa.sin_addr,
                             sizeof(sa.sin_addr), AF_INET)))
    perror("id_lookup_username(): gethostbyaddr");
  else
  {
    /* connect to the inetd super server */

    saddr.sin_family = hent->h_addrtype;
    saddr.sin_port   = htons(IDENTD_PORT);
    memcpy(&saddr.sin_addr, hent->h_addr, hent->h_length);

    if ((sock = socket(hent->h_addrtype, SOCK_STREAM, 0)) < 0)
    {
      perror("id_lookup_username(): socket");
      return NULL;
    }

    if (connect(sock, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)
    {
      if (errno != ECONNREFUSED)
        perror("id_lookup_username(): connect");
      close(sock);
      return NULL;
    }

    /* write our message to the inetd super server */
    write(sock, &string, strlen(string));

    /* get the reply */
    read(sock, string, 256);

    /* close the socket */
    close(sock);

    /* extract what we need */
    {
      int sport, cport;
      char mtype[256], otype[256];

      sscanf(string, " %d , %d : %s : %s : %s ", &sport, &cport,
             mtype, otype, username);

      if (!strcmp(mtype, "USERID"))
	return username;
      else
        return NULL;
    }
  }

  return NULL;
}