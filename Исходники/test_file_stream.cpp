  void testReOpen ()
  {
    list<string> filters;
    LogStream* ls;
    File f;
    char buf[128];
    size_t nbr;
    string message1;
    string message2;
    ostringstream oss;
    LoggingLevel level = MYSERVER_LOG_MSG_INFO;

    oss << "message1" << endl;
    message1.assign (oss.str ());
    oss.str ("message2");
    oss << endl;
    message2.assign (oss.str ());

    try
      {
        FilesUtility::deleteFile ("foo");
      }
    catch (...)
      {
      }
    ls = fsc->create (ff, "foo", filters, 0);
    CPPUNIT_ASSERT (ls);
    ls->log (message1, level);
    ls->close ();
    delete ls;

    ls = fsc->create (ff, "foo", filters, 0);
    CPPUNIT_ASSERT (ls);
    ls->log (message2, level);
    ls->close ();
    delete ls;

    f.openFile ("foo", File::READ | File::OPEN_IF_EXISTS);
    f.read (buf, 128, &nbr);
    f.close ();
    buf[nbr] = '\0';
    CPPUNIT_ASSERT_EQUAL (nbr, (size_t)(message1.length () + message2.length ()));
    CPPUNIT_ASSERT (!string (buf).compare (message1.append (message2)));
  }