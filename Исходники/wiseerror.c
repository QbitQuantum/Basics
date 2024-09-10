boolean add_log_filename(char * filename)
{
  register FILE * ofp;
  if( (ofp=openfile(filename,"w")) == NULL) {
    warn("Could not open %s as a log filename",filename);
    return FALSE;
  }
  
  add_log_file(ofp);
  return TRUE;
}