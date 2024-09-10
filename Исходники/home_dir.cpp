/*!
  Load the internal buffer.
 */
int HomeDir::loadImpl ()
{
#ifdef WIN32
  DWORD len = 64;
  char *buf;
  buf = new char[len];

  if (GetProfilesDirectory (buf, &len) == FALSE)
    {
      delete [] buf;
      buf = new char[len];
      if (GetProfilesDirectory (buf, &len) == FALSE)
        {
          delete [] buf;
          return 1;
        }
    }
  data.assign (buf);
#elif !HAVE_GETPWNAM
  File usersFile;
  u_long size;
  char* buffer;
  u_long read;
  u_long counter;

  clear ();

  if (usersFile.openFile ("/etc/passwd", File::READ |
                          File::OPEN_IF_EXISTS))
    return 1;
  size = usersFile.getFileSize ();
  timestamp = usersFile.getLastModTime ();
  if (size == (u_long) -1)
    {
      usersFile.close ();
      return 1;
    }

  buffer = new char[size+1];

  usersFile.read (buffer, size, &read);
  buffer[read] = '\0';

  for (counter = 0; counter < read; counter++)
    if (buffer[counter] == ':')
      buffer[counter] = '\0';

  for (counter = 0; counter < size;)
    {
      char *username = 0;
      char *home = 0;
      string sUsername;
      string *sHome;
      string *old;

      if (buffer[counter] == '#')
        {
          while (buffer[counter++] != '\n');
          continue;
        }

      /* Username.  */
      username = &buffer[counter];

      while (buffer[counter++] != '\0');
      /* Password.  */

      while (buffer[counter++] != '\0');
      /* User ID.  */

      while (buffer[counter++] != '\0');
      /* Group ID.  */

      while (buffer[counter++] != '\0');
      /* Info.  */

      while (buffer[counter++] != '\0');
      /* Home.  */

      home = &buffer[counter++];
      sUsername = string (username);
      sHome = new string (home);

      old = data.put (sUsername, sHome);

      if (old)
        delete old;

      while (buffer[counter++] != '\0');
      /* Shell.  */

      while (buffer[counter++] != '\n');
      /* Next tuple.  */
  }
  delete [] buffer;
  usersFile.close ();
#endif

  loaded = 1;
  return 0;
}