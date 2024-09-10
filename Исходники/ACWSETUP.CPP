void get_replay_name (const char *filename, char *namebuf) {
  FILE *in = fopen(filename, "rb");
  if (in == NULL)
    return;

  char buffer [100];
  fread (buffer, 12, 1, in);
  buffer[12] = 0;
  if (strcmp (buffer, "AGSRecording") != 0) {
    fclose (in);
    return;
  }

  fgetstring_limit (buffer, in, 12);
  if (buffer[0] != '2')  {
    // very first alpha version, can't play it
    fclose (in);
    return;
  }
  int replayver = getw(in);

  if ((replayver < 1) || (replayver > 3)) {
    fclose (in);
    return;
  }

  namebuf[0] = 0;
  if (strcmp (buffer, enginever))
    strcpy (namebuf, "!! ");

  if (replayver == 1) {
    // first version didn't save info
    strcat (namebuf, "(unknown replay)");
    fclose (in);
    return;
  }

  fgetstring_limit (buffer, in, 99);
  // skip the UID
  getw (in);
  strcat (namebuf, buffer);
  strcat (namebuf, " (");
  // skip the total time
  int tottime = getw (in);
  sprintf (&namebuf[strlen(namebuf)], "%02d:%02d:%02d)", tottime / 3600, (tottime % 3600) / 60, tottime % 60);
  // replay description, maybe we'll use this later
  fgetstring_limit (buffer, in, 99);

  if (buffer[0] == 0)
    strcpy (buffer, "No description");

  strcat (namebuf, ": ");
  strcat (namebuf, buffer);
  fclose (in);

}