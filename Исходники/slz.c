void writechar(register unsigned char outchar, register FILE *outfile)
{
  if (putc(outchar,outfile)==EOF)
    {
      printf("Error writing output file.\n");
      fcloseall();
      exit(slz_error + error_write);
    }
  LZ_history[lzhist_offset]=outchar; lzhist_offset=(lzhist_offset+1)&MASK_history;
}