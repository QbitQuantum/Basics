int main(int argc, char **argv)
{
  Connection con;
  PortConnection port;
  const char *name = TIMING_NAME;
  const char *other, *now;

  struct sigaction sa;
  sa.sa_handler= SIG_IGN;
  sa.sa_flags=SA_NOCLDWAIT;
  /* this old code produced a warning 
    struct sigaction sa = {
    SIG_IGN, 0, 0, SA_NOCLDWAIT
    };*/

  x = time(0);

  sigaction (SIGCHLD, &sa, 0);

  {
    char buf[1024];
    FILE *x;

    x = fopen ("modulus.hex", "r");
    if (! x) { perror ("modulus.hex"); exit (2); }
    fgets (buf, 1024, x);
    fclose (x);
    LHex2Long (buf, &n);
  }

  /***************  Globales Port eröffnen  ***************/
  if (!(port=OpenPort(name))) {
    fprintf(stderr,"TIMING_DAEMON: Kann das Dämon-Port \"%s\" nicht erzeugen: %s\n",name,NET_ErrorText());
    exit(20);
  }

  /******************* Hauptschleife **********************/
  while (1) {

    /**************  Auf Verbindung auf dem Port warten  ****************/
    if (!(con=WaitAtPort(port))) {
      fprintf(stderr,"TIMING_DAEMON: WaitAtPort ging schief: %s\n",NET_ErrorText());
      exit(20);
    }
    other = PeerName(port);
    now = Now();

    fprintf (stderr, "Connect from %s: %s\n", other, now);
    fflush (stderr);

    x += time(0);
    handle_connection (con, other, now);
    DisConnect (con);
  }

  return 0;
}