main()
{
  handle = Fcreate ("READ.ME", LECT_SEUL);
  
  if (handle < 0)
    printf ("Erreur … l'ouverture du fichier!\n");
  else
  {
    Fwrite (handle, (long) strlen (ligne), ligne);
    Fclose (handle);
  }
}