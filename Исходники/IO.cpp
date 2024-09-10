void
JAWS_Asynch_IO::receive_file (JAWS_IO_Handler *ioh,
                              const char *filename,
                              void *initial_data,
                              unsigned int initial_data_length,
                              unsigned int entire_length)
{
  JAWS_TRACE ("JAWS_Asynch_IO::receive_file");

  ioh->idle ();

  JAWS_Asynch_IO_Handler *aioh =
    dynamic_cast<JAWS_Asynch_IO_Handler *> (ioh);

  ACE_Message_Block *mb = 0;
  ACE_Filecache_Handle *handle;

  ACE_NEW (handle, ACE_Filecache_Handle (filename, entire_length, ACE_NOMAP));

  int result = handle->error ();

  if (result == ACE_Filecache_Handle::ACE_SUCCESS)
    {
      ACE_OS::memcpy (handle->address (),
                      initial_data,
                      initial_data_length);

      int bytes_to_read = entire_length - initial_data_length;

      ACE_NEW (mb, ACE_Message_Block ((char *)handle->address ()
                                      + initial_data_length, bytes_to_read));

      if (mb == 0)
        {
          errno = ENOMEM;
          result = -1;
        }
      else
        {
          ACE_Asynch_Read_Stream ar;

          if (ar.open (*(aioh->handler ()), aioh->handle ()) == -1
              || ar.read (*mb, mb->size () - mb->length (), handle) == -1)
            result = -1;
        }
    }

  if (result != ACE_Filecache_Handle::ACE_SUCCESS)
    {
      this->handler_->receive_file_error (result);
      delete mb;
      delete handle;
    }
}