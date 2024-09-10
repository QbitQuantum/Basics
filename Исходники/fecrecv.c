int main (int argc, char *argv[])
{
  struct sockaddr_in sin;
  int sock, len;
  char p[4096], *fname = "x.fec";
  struct timeval tv;
  fd_set set;
  FILE *f;
  fecDecoder *d;
  struct ip_mreq mreq;
#if defined (WIN32) || defined (__CYGWIN__)
  WSADATA localWSA;
  if (WSAStartup (MAKEWORD(1,1),&localWSA) != 0) {
    fprintf (stderr, "Unable to load wsock32.dll\n");
    mainreturn (1);
  }
#endif

  fprintf (stderr, "%s: %s\n", argv[0], FEC_COPYRIGHT);

  if ((sock = socket (PF_INET, SOCK_DGRAM, 0)) == -1) {
    fprintf (stderr, "Unable to make internet socket\n");
    mainreturn (3);
  }
  memset (&sin, 0, sizeof (sin));
  sin.sin_family = AF_INET;
  *(unsigned*)&sin.sin_addr = 0; //inet_addr (iface);
  sin.sin_port = SUGGESTED_FEC_UDP_PORT_NUMBER;

  for (;argc > 1; argc--, argv++) {
    if (strcmp (argv[1], "-h") == 0) {
      fprintf (stderr, 
"Usage : %s [-f %s] [-p portNumber] [-i interface] [-m multicastAddress]\n"
"Receives a file and exits. If the file was received successfully\n"
"it is called `%s' (adjustable with -f), otherwise it is deleted.\n"
"Note that the interface is the IP address of the local device\n",
        argv[0], fname, fname);
      mainreturn (4);
    }
    else if (strcmp (argv[1], "-f") == 0) {
      fname = argv[2];
      argc--, argv++;
    }
    else if (strcmp (argv[1], "-p") == 0) {
      sin.sin_port = htons (atoi (argv[2]));
      argc--, argv++;
    }
    else if (strcmp (argv[1], "-i") == 0) {
      *(unsigned*)&sin.sin_addr = inet_addr (argv[2]);
      argc--, argv++;
    }
    else if (strcmp (argv[1], "-m") == 0) {
      *(unsigned*)&mreq.imr_multiaddr = inet_addr (argv[2]);
      *(unsigned*)&mreq.imr_interface = *(unsigned*)&sin.sin_addr;
      if (setsockopt (sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq,
      sizeof(mreq)) < 0) fprintf (stderr, "Unable to active multicast\n");
    }
    else fprintf (stderr, "Unknown option %s. Use -h for help\n", argv[1]);
  }

  if (bind (sock, (struct sockaddr*) &sin, sizeof (sin)) == -1) {
    fprintf (stderr, "Error : UDP port or device is unavailable\n");
    mainreturn (1);
  }
  f = fopen (fname, "w");
  d = NewFecDecoder (f, WriteF);
  do {
    len = recv (sock, p, sizeof (p), 0);
    FecDecode (p, len, 1, d);
    FD_ZERO (&set);
    FD_SET (sock, &set);
    tv.tv_sec = 30;
    tv.tv_usec = 0;
  } while (select (sock + 1, &set, NULL, NULL, &tv) != 0);
  FlushFecDecoder (d);

  fclose (f);

  fprintf (stderr, "File received. %d packets was unrecoverable out of %d\n",
    d->lostPackets,
    (d->lostPackets + d->receivedPackets + d->correctedPackets));
  if (d->lostPackets > 0) unlink (fname);

  closesocket (sock);
  mainreturn (0);
}