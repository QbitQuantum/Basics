void
JAWS_Config_File_Impl::parse_file (void)
{
  ACE_FILE_Connector fconnector;
  ACE_FILE_IO fio;

  if (fconnector.connect ( fio
                         , this->faddr_
                         , 0
                         , ACE_Addr::sap_any
                         , 0
                         , O_RDONLY
                         ) == -1)
    return;

  ACE_Message_Block buffer (8192);
  ACE_Message_Block line (4096);
  ssize_t count = 0;
  const ACE_TCHAR *sym_name;
  const ACE_TCHAR *sym_value;
  int last_line_was_read = 0;
  ACE_TCHAR *end_of_current_line = 0;
  ACE_TCHAR *p = 0;

  while (last_line_was_read
         || (count = fio.recv (buffer.wr_ptr (), buffer.space () - 2)) >= 0)
    {
      end_of_current_line = 0;

      // Make sure input is newline terminated if it is the last line,
      // and always null terminated.
      if (! last_line_was_read)
        {
          if (count > 0)
            {
              buffer.wr_ptr (count);
              // Scan forward for at least one newline character
              p = buffer.rd_ptr ();
              while (p != buffer.wr_ptr ())
                {
                  if (*p == '\n')
                    break;
                  p++;
                }

              if (p == buffer.wr_ptr ())
                continue;

              end_of_current_line = p;
            }
          else
            {
              if (buffer.wr_ptr ()[-1] != '\n')
                {
                  buffer.wr_ptr ()[0] = '\n';
                  buffer.wr_ptr (1);
                }

              last_line_was_read = 1;
            }

          buffer.wr_ptr ()[0] = '\0';
        }

      if (end_of_current_line == 0)
        {
          end_of_current_line = buffer.rd_ptr ();
          while (*end_of_current_line != '\n')
            end_of_current_line++;
        }

      // If buffer is not pointing to a continuation line, or there is
      // no more input, then can commit the scanned configuration
      // line.
      if (line.length () != 0
          && ((last_line_was_read && buffer.length () == 0)
              || (buffer.rd_ptr ()[0] != ' '
                  && buffer.rd_ptr ()[0] != '\t')))
        {
          ACE_TCHAR *name = 0;
          ACE_TCHAR *value = 0;

          name = line.rd_ptr ();
          for (p = name; *p != '\0'; p++)
            {
              if (*p == '=')
                {
                  line.rd_ptr (p+1);
                  while (p != name && (p[-1] == ' ' || p[-1] == '\t'))
                    p--;
                  *p = '\0';
                }
            }

          if (*name)
            {
              value = line.rd_ptr ();
              while (*value == ' ' || *value == '\t')
                value++;
              p = line.wr_ptr ();
              while (p != value && (p[-1] == ' ' || p[-1] == '\t'))
                p--;
              *p = '\0';

              sym_name = this->strings_->duplicate (name);
              sym_value = this->strings_->duplicate (value);
              this->symbols_->rebind (sym_name, sym_value);
            }

          line.reset ();
        }

      // If we are done, we are done!
      if (last_line_was_read && buffer.length () == 0)
        break;

      // If the buffer is pointing at a comment line, ignore it.
      if (buffer.rd_ptr ()[0] == '#'
          || buffer.rd_ptr ()[0] == '\n'
          || (buffer.rd_ptr ()[0] == '\r' && buffer.rd_ptr ()[1] == '\n'))
        {
          buffer.rd_ptr (end_of_current_line + 1);
          buffer.crunch ();
          continue;
        }

      // Whatever is left is either the start of a name-value-pair or a
      // continuation of one.
      line.copy (buffer.rd_ptr (),
                 end_of_current_line - buffer.rd_ptr ());
      p = line.wr_ptr ();
      while (p != line.rd_ptr () && (p[-1] == ' ' || p[-1] == '\t'))
        p--;
      line.wr_ptr (p);
      line.wr_ptr ()[0] = '\0';
      buffer.rd_ptr (end_of_current_line + 1);
      buffer.crunch ();
    }

  fio.close ();
}