int 
main (int argc, char **argv)
{
  if (!aa_parseoptions (NULL, NULL, &argc, argv) || argc != 1)
    {
      printf ("%s", aa_help);
      exit (1);
    }
  initialize ();
  game ();
  uninitialize ();
  return 1;
}