int dexpand_c(char *templat,char *output,int length)
/*
  This expands wildcards, matching them with files.

  Input:
    templat	The input character string, containing the wildcards.
    length	The length of the output buffer.
  Output:
    output	All the files matching "template". Filenames are separated
		by commas.
------------------------------------------------------------------------*/
{
  FILE *fd;
  char line[MAXPATH],*s;
  int l;

  Strcpy(line,"echo ");
  Strcat(line,templat);
  fd = popen(line,"r");
  if(fd == NULL) return(-1);
  s = output;
  while(fgets(s,length,fd)){
    l = strlen(s);
    if( length-l <= 1 ){(void)pclose(fd); return(-1);}
    *(s+l-1) = ',';
    s += l;
    length -= l;
  }
  if(s != output) *--s = 0;
  (void)pclose(fd);
  return(s-output);
}