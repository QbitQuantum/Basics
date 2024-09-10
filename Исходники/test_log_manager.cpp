  void testCycleWithGzipChain ()
  {
    u_long cycleLog = 40;
    list<string> filters;
    string message ("The quick brown fox jumped over the lazy dog.");
    string message1 ("Yet another short log message.");
    string gotMessage;
    string gotMessage1;
    File f;
    char gzipComp[128];
    char gzipDecomp[128];
    GzipDecompress gzdc;
    size_t nbr = 0;
    list<string> cs;
    list<string>::iterator it;
    LogStream* ls = NULL;

    try
      {
        FilesUtility::deleteFile ("fooc");
      }
    catch (...)
      {
      }

    filters.push_back ("gzip");
    lm->add (this, "test", "file://fooc", filters, cycleLog);
    lm->log (this, "test", "file://fooc", message);
    lm->log (this, "test", "file://fooc", message1);
    f.openFile ("fooc", File::READ | File::OPEN_IF_EXISTS);
    f.read (gzipComp, 128, &nbr);
    f.close ();
    gzdc.decompress (&gzipComp[gzdc.headerSize ()],
                     nbr - gzdc.headerSize (),
                     gzipDecomp, 128);
    gzipDecomp[message1.size ()] = '\0';
    gotMessage1.assign (gzipDecomp);
    lm->get (this, "test", "file://fooc", &ls);
    CPPUNIT_ASSERT (ls);
    cs = ls->getCycledStreams ();
    for (it = cs.begin (); it != cs.end (); it++)
      {
        f.openFile (*it, File::READ | File::OPEN_IF_EXISTS);
        f.read (gzipComp, 128, &nbr);
        f.close ();
        gzdc.decompress (&gzipComp[gzdc.headerSize ()],
                         nbr - gzdc.headerSize (),
                         gzipDecomp, 128);
        gzipDecomp[message.size ()] = '\0';
        gotMessage.assign (gzipDecomp);

        try
          {
            FilesUtility::deleteFile (*it);
          }
        catch (...)
          {
          }
      }
    lm->close (this);

    try
      {
        FilesUtility::deleteFile ("fooc");
      }
    catch (...)
      {
      }

    CPPUNIT_ASSERT (!message1.compare (gotMessage1));
    CPPUNIT_ASSERT (!message.compare (gotMessage));
  }