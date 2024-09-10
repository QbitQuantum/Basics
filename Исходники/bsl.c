int
bsl_apply (const char *mod, const char *bslname)
{
  FILE *modfile, *bslfile;
  unsigned char byte;
  char buf[4096], modname[FILENAME_MAX];
  int data, nbytes, offset;

  strcpy (modname, mod);
  ucon64_file_handler (modname, NULL, 0);
  fcopy (mod, 0, fsizeof (mod), modname, "wb"); // no copy if one file

  if ((modfile = fopen (modname, "r+b")) == NULL)
    {
      fprintf (stderr, ucon64_msg[OPEN_WRITE_ERROR], modname);
      return -1;
    }
  if ((bslfile = fopen (bslname, "rb")) == NULL)
    {
      fprintf (stderr, ucon64_msg[OPEN_WRITE_ERROR], bslname);
      return -1;
    }

  printf ("Applying BSL/Baseline patch...\n");

  while (!feof (bslfile))                       // we could use 1, but feof() makes it fail-safe
    {
      fscanf (bslfile, "%d\n", &offset);
      fscanf (bslfile, "%d\n", &data);
      if ((offset == -1) && (data == -1))
        break;

      fseek (modfile, offset, SEEK_SET);
      fputc (data, modfile);
    }

  fscanf (bslfile, "%d\n", &offset);
  fscanf (bslfile, "%d\n", &nbytes);
  fseek (modfile, offset, SEEK_SET);
  if (nbytes > 0)
    {
      while (nbytes > 4096)
        {
          fread (buf, 4096, 1, bslfile);
          fwrite (buf, 4096, 1, modfile);
          nbytes -= 4096;
        }
      while (nbytes-- >= 0)                     // yes, one byte more than the
        {                                       //  _value_ read from the BSL file
          byte = fgetc (bslfile);
          fputc (byte, modfile);
        }
    }

  printf ("Patching complete\n\n");
  printf (ucon64_msg[WROTE], modname);
  printf ("\n"
          "NOTE: Sometimes you have to add/strip a 512 bytes header when you patch a ROM\n"
          "      This means you must modify for example a SNES ROM with -swc or -stp or\n"
          "      the patch will not work\n");

  fclose (bslfile);
  fclose (modfile);

  return 0;
}