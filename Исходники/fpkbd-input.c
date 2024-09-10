void press_key(int fd, int key, int value) 
{
  if (key>0) 
    {
      static struct input_event event={
	.type = EV_KEY
      };
      const static struct input_event syn_event={
	.type = EV_SYN,
	.code = SYN_REPORT,
	.value = 0
      };
      
      event.code=key;
      event.value=value;

      write(fd, &event, sizeof(event));
      write(fd, &syn_event, sizeof(event));
    }
}

int main(int argc, char **argv)
{
  int rfd=0, wfd=0, res=0;
  unsigned char buf[16];
  typedef unsigned long long keystate;
  
  int opt;
  unsigned char do_fork=1;
  
  while ((opt = getopt(argc, argv, "f")) != -1) 
    {
      switch (opt) 
	{
	case 'f':
	  do_fork = 0;
	  break;
	default:
	  fprintf (stderr, "Invalid option: -%c\n", opt);
	  return 1;
	}
    }

  if (argc > optind+1) 
    {
      fprintf (stderr, "Usage: %s [device]\n", *argv);
      exit(1);
    }
  if (argc == optind+1) 
    {
      if ((rfd = open (argv[optind], O_RDONLY)) <= 0) 
	{
	  perror (argv[optind]);
	  return 1;
	}
    }
  else 
    {
      rfd=open_kb();
    }
  
  wfd=open_uinput();
  
  if (rfd <= 0) 
    {
      puts ("failed to find keyboard");
      return 1;
    }
  
  if (do_fork) 
    {
      switch(fork())
	{
	case -1:
	  perror ("fork");
	  return 1;
	case 0:
	  break;
	default:
	  return 0;
	}
    }

  keystate prev=0, cur=0;
  while ((res = read(rfd, buf, 16)) > 0) 
    {
      cur=*((keystate*)(buf+2));
      
      if (cur && (cur != prev)) 
	{
	  keystate cur_new = cur & (cur ^ prev);
	  keystate cur_old = prev & (cur ^ prev);

	  if (cur_new || cur_old) 
	    {
	      int i;
	      keystate b;
	      for (i=0, b=1; positions[i]!=0; ++i, b<<=1) 
		{
		  if (cur_old & b)
		    press_key(wfd,positions[i], 0);
		  else if (cur_new & b)
		    press_key(wfd,positions[i], 1);
		}
	      prev=cur;
	    }
	}
    }

  close(rfd);
  ioctl(wfd, UI_DEV_DESTROY);
  close(wfd);

  return 0;
}