// Return the CBM-style load address..
// TODO: figure out where this belongs!
unsigned int DVfs::getStartAddress(const char *filename)
{
  if(!filename) return 0;
  diskError=false;
  if(disk[diskNum]) {
    // NOTE: fopen, etc are OUR versions, not the standard C ones...
    void *fd=Fopen(filename,"rb");
    if(!fd) {
      return 0;
    }
    BYTE l,h;
    Fread(&l,1,1,fd);
    Fread(&h,1,1,fd);
    unsigned int saddr=(h*256)+l;
    Fclose(fd);
    return saddr;
  }
  else noSuchDisk();
  return 0;
}