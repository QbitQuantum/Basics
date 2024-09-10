static bool loadimage(
        struct userdata *ud,
        char const      *restrict filename,
        char const      *restrict taddr
)
{
  mc6809addr__t  addr;
  FILE          *fp;
  char          *ro;
  int            c;
  
  assert(ud       != NULL);
  assert(filename != NULL);
  assert(taddr    != NULL);
  
  addr = strtoul(taddr,&ro,16);
  if (*ro != 'r')
    ro = NULL;
    
  fp = fopen(filename,"rb");
  if (fp == NULL)
    return false;
    
  while((c = fgetc(fp)) != EOF)
  {
    ud->memory[addr] = c;
    if (ro)
      ud->readonly[addr] = true;
    addr++;
  }
  