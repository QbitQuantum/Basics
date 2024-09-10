void send_freq_to_FT817( double frequency )
{
  fd_set fds;
  int count;
  struct timeval tv;
  unsigned char command[12];
  char ghz,hmhz,dmhz,mhz,hkhz,dkhz,khz,hhz;

  frequency=frequency*10.0;

  ghz =(frequency-fmod(frequency,10000000))/10000000;
  frequency=fmod(frequency,10000000);
  hmhz=(frequency-fmod(frequency,1000000))/1000000;
  frequency=fmod(frequency,1000000);
  dmhz=(frequency-fmod(frequency,100000))/100000;
  frequency=fmod(frequency,100000);
  mhz =(frequency-fmod(frequency,10000))/10000;
  frequency=fmod(frequency,10000);
  hkhz=(frequency-fmod(frequency,1000))/1000;
  frequency=fmod(frequency,1000);
  dkhz=(frequency-fmod(frequency,100))/100;
  frequency=fmod(frequency,100);
  khz =(frequency-fmod(frequency,10))/10;
  frequency=fmod(frequency,10);
  hhz =frequency;
  frequency=fmod(frequency,10);
  hhz =frequency;

  command[0]=(hmhz<<4)|dmhz;
  command[1]=(mhz<<4)|hkhz;
  command[2]=(dkhz<<4)|khz;
  command[3]=(hhz<<4)|dhz;
  command[4]=0x01;

  /* Send it */
#ifdef DEBUG
  fprintf( stderr, "FT817: Sending command ... ");
  {int i;
  for(i=0;i<11;i++) fprintf(stderr," %02X",command[i]);
  fprintf(stderr,"\n");
  }
#endif

  FD_ZERO(&fds);
  FD_SET(port, &fds);
  tv.tv_sec = 5;
  tv.tv_usec = 0;

  if (select(port+1, NULL, &fds, NULL, &tv)) {
    if ((count = write(port, command, 11)) == -1) {
      perror("write");
      return;
    }
  }
  else {
    fprintf( stderr,"FT817: Timeout sending command !!!\n");
    perror("select");
    return;
  }
}