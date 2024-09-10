static guchar
g_scanner_peek_next_char (GScanner *scanner)
{
  if (scanner->text < scanner->text_end)
    {
      return *scanner->text;
    }
  else if (scanner->input_fd >= 0)
    {
      gint count;
      gchar *buffer;

      buffer = scanner->buffer;
      do
	{//scott
	  //count = read (scanner->input_fd, buffer, READ_BUFFER_SIZE);
		count = fread (buffer,1,READ_BUFFER_SIZE, _wfdopen( scanner->input_fd,L"r") );
	}
      while (count == -1 && (glib_errno == EINTR || glib_errno == EAGAIN));

      if (count < 1)
	{
	  scanner->input_fd = -1;

	  return 0;
	}
      else
	{
	  scanner->text = buffer;
	  scanner->text_end = buffer + count;

	  return *buffer;
	}
    }
  else
    return 0;
}