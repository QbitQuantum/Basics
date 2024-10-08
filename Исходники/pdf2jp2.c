int main(int argc, char *argv[])
{
#define NUMJP2 32
  int i, c = 0;
  long offets[NUMJP2];
  char buffer[512];
#define BUFLEN 4096
  int cont = 1;
  FILE *f;
  size_t nread;
  char haystack[BUFLEN];
  const char needle[] = "JPXDecode";

  const size_t nlen = strlen( needle );
  const size_t flen = BUFLEN - nlen;
  char *fpos = haystack + nlen;
  const char *filename;
  if( argc < 2 ) return 1;

  filename = argv[1];

  memset( haystack, 0, nlen );

  f = fopen( filename, "rb" );
  while( cont )
    {
    const char *ret;
    size_t hlen;
    nread = fread(fpos, 1, flen, f);
    hlen = nlen + nread;
    ret = memmem( haystack, hlen, needle, nlen);
    if( ret )
      {
      const long cpos = ftell(f);
      const ptrdiff_t diff = ret - haystack;
      assert( diff >= 0 );
      /*fprintf( stdout, "Found it: %lx\n", (ptrdiff_t)cpos - (ptrdiff_t)hlen + diff);*/
      offets[c++] = (ptrdiff_t)cpos - (ptrdiff_t)hlen + diff;
      }
    cont = (nread == flen);
    memcpy( haystack, haystack + nread, nlen );
    }

  assert( feof( f ) );

  for( i = 0; i < c; ++i )
    {
    int s, len = 0;
    char *r;
    const int ret = fseek(f, offets[i], SEEK_SET);
    assert( ret == 0 );
    r = fgets(buffer, sizeof(buffer), f);
    assert( r );
    /*fprintf( stderr, "DEBUG: %s", r );*/
    s = sscanf(r, "JPXDecode]/Length  %d/Width %*d/BitsPerComponent %*d/Height %*d", &len);
    assert( s == 1 );
      {
      FILE *jp2;
      int j;
      char jp2fn[512];
      sprintf( jp2fn, "%s.%d.jp2", filename, i );
      jp2 = fopen( jp2fn, "wb" );
      for( j = 0; j < len; ++j )
        {
        int v = fgetc(f);
        int ret2 = fputc(v, jp2);
        assert( ret2 != EOF );
        }
      fclose( jp2 );
#if 0
      /* TODO need to check we reached endstream */
      r = fgets(buffer, sizeof(buffer), f);
      fprintf( stderr, "DEBUG: [%s]", r );
      r = fgets(buffer, sizeof(buffer), f);
      fprintf( stderr, "DEBUG: [%s]", r );
#endif
      }
    }
  fclose(f);

  return 0;
}