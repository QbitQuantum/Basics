static int
test_ostream (void)
{
  // This message should show up in the log file.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("first message\n")));

  ACE_LOG_MSG->clr_flags (ACE_Log_Msg::OSTREAM);

  // This message should not show up anywhere.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("second message\n")));

  ACE_LOG_MSG->set_flags (ACE_Log_Msg::OSTREAM);

#if !defined (ACE_LACKS_IOSTREAM_TOTALLY)
  // Create a persistent store.
  const ACE_TCHAR *filename = ACE_TEXT ("output");
  ofstream myostream (ACE_TEXT_ALWAYS_CHAR (filename), ios::out | ios::trunc);

  // Check for errors.
  if (myostream.bad ())
    return -1;

  // Set the ostream.
  ACE_LOG_MSG->msg_ostream (&myostream);

  // This message should show up in the ostream.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("fourth message\n")));
  // Set the ostream back to the test's log file.
  ACE_LOG_MSG->msg_ostream (ace_file_stream::instance ()->output_file ());
  // Now close the ostream file and check its contents.
  myostream.close ();

  ACE_FILE_Connector connector;
  ACE_FILE_IO file;

  // Open up the file.
  if (connector.connect (file,
                         ACE_FILE_Addr (filename)) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("connect failed for %p\n"),
                         filename),
                        1);
    }

  // Unlink this file right away so that it is automatically removed
  // when the process exits.Ignore error returns in case this operation
  // is not supported.
  ACE_OS::unlink(filename);

  ACE_FILE_Info info;
  if (file.get_info (info) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("get_info failed on %p\n"),
                         filename),
                        -1);
    }

  // Allocate the input buffer
  char *buffer;
  ACE_NEW_RETURN (buffer,
                  char[info.size_ + 1],
                  -1);
  // Make sure <buffer> is released automagically.
  ACE_Auto_Basic_Array_Ptr<char> b (buffer);

  // Read the file into the buffer.
  ssize_t size = file.recv (buffer,
                            info.size_);
  if (size != info.size_)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("Read %d bytes, rather than expected %d bytes\n"),
                         size,
                         info.size_),
                        -1);
    }
  // Make sure to NUL-terminate this turkey!
  buffer[size] = '\0';


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%s"),
              buffer));

#endif /* ACE_LACKS_IOSTREAM_TOTALLY */

  // This message should show up in stderr and the ostream (without
  // ACE_LACKS_IOSTREAM_TOTALLY).
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("fifth message\n")));

  return 0;
}