int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  parse_args (argc, argv);
  void *cp;
  char buf[BUFSIZ];
  ACE_TLI_Stream sc;
  ACE_TLI_Connector con;

  if (con.connect (sc,
                   ACE_INET_Addr (port_number,
                                  host_name)) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "open"),
                      -1);

  ACE_Mem_Map mmap (file_name, PROT_READ);

  if (mmap (cp) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",

                       "mmap"), -1);

  // Next, send the file's contents.

  if (sc.send_n (cp, mmap.size ()) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",

                       "send_n"), -1);

  if (sc.sndrel () == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "close_writer"),
                      -1);

  for (int n; (n = sc.recv (buf, sizeof buf)) > 0; )
    if (ACE_OS::write (ACE_STDOUT, buf, n) != n)
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%p\n",
                         "write"),
                        -1);

  if (sc.close () == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "close"),
                      -1);
  return 0;
}