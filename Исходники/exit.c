int main(void)
{
  int fd;
  char c;

  if ((fd = open("_cexit.c",O_RDONLY)) < 0)
  {
	printf("Unable to open _cexit.c for reading\n");
	return 1;
  }
  atexit(exit_func);
  if (read(fd,&c,1) != 1)

printf("Unable to read from open file handle %d before _cexit\n",fd);
  else
	printf("Successfully read from open file handle %d before _cexit\n",fd);
  _cexit();
  if (read(fd,&c,1) == 1)
	  MessageBeep(0);
  return 0;
}