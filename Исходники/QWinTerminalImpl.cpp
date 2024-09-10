QConsolePrivate::QConsolePrivate (QWinTerminalImpl* parent, const QString& cmd)
    : q (parent), m_command (cmd), m_process (NULL), m_inWheelEvent (false)
{
  //log (NULL);

  // Possibly detach from any existing console
  log ("Detaching from existing console (if any)...\n");
  FreeConsole ();
  log ("Closing standard IO...\n");
  closeStandardIO (0, STD_INPUT_HANDLE, "STDIN");
  closeStandardIO (1, STD_OUTPUT_HANDLE, "STDOUT");
  closeStandardIO (2, STD_ERROR_HANDLE, "STDERR");

#ifdef HIDDEN_CONSOLE
  HWINSTA hOrigSta, hNewSta;

  // Create new (hidden) console
  hOrigSta = GetProcessWindowStation ();
  hNewSta = CreateWindowStation (NULL, 0, GENERIC_ALL, NULL);
  log ("Current Windows station: %p.\nNew Windows station: %p.\n", hOrigSta,
       hNewSta);
  if (! SetProcessWindowStation (hNewSta))
    log ("Failed to switch to new Windows station.\n");
#endif
  if (! AllocConsole ())
    log ("Failed to create new console.\n");
#ifdef HIDDEN_CONSOLE
  if (! SetProcessWindowStation (hOrigSta))
    log ("Failed to restore original Windows station.\n");
  if (! CloseWindowStation (hNewSta))
    log ("Failed to close new Windows station.\n");
#endif

  log ("New (hidden) console created.\n");

  setupStandardIO (STD_INPUT_HANDLE,  0, "STDIN",  "CONIN$");
  setupStandardIO (STD_OUTPUT_HANDLE, 1, "STDOUT", "CONOUT$");
  setupStandardIO (STD_ERROR_HANDLE,  2, "STDERR", "CONOUT$");

  log ("Standard input/output/error set up.\n");

  *stdin = *(fdopen (0, "rb"));
  *stdout = *(fdopen (1, "wb"));
  *stderr = *(fdopen (2, "wb"));

  log ("POSIX standard streams created.\n");

  setvbuf (stdin, NULL, _IONBF, 0);
  setvbuf (stdout, NULL, _IONBF, 0);
  setvbuf (stderr, NULL, _IONBF, 0);

  log ("POSIX standard stream buffers adjusted.\n");

  HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);

  log ("Console allocated: hStdOut: %p\n", hStdOut);

  m_stdOut = hStdOut;
  m_consoleWindow = GetConsoleWindow ();

  // In case the console window hasn't been created hidden...
  ShowWindow (m_consoleWindow, SW_HIDE);

  CONSOLE_SCREEN_BUFFER_INFO sbi;

  GetConsoleScreenBufferInfo (hStdOut, &sbi);
  m_bufferSize = QSize (sbi.dwSize.X, qMax (sbi.dwSize.Y, (SHORT)500));
  m_consoleRect = QRect (sbi.srWindow.Left, sbi.srWindow.Top,
                         sbi.srWindow.Right - sbi.srWindow.Left + 1,
                         sbi.srWindow.Bottom - sbi.srWindow.Top + 1);
  m_cursorPos = QPoint (sbi.dwCursorPosition.X, sbi.dwCursorPosition.Y);

  log ("Initial console parameters:\n");
  log ("  buffer size: %d x %d\n", m_bufferSize.width (),
       m_bufferSize.height ());
  log ("  window: (%d, %d) -> (%d, %d) [%d x %d]\n",
       m_consoleRect.left (), m_consoleRect.top (),
       m_consoleRect.right (), m_consoleRect.bottom (),
       m_consoleRect.width (), m_consoleRect.height ());

  wchar_t titleBuf[260];
  GetConsoleTitleW (titleBuf, sizeof (titleBuf));
  q->setWindowTitle (QString::fromWCharArray (titleBuf));

  m_font.setFamily ("Lucida Console");
  m_font.setPointSize (9);
  m_font.setStyleHint (QFont::TypeWriter);
  m_backgroundColor = Qt::white;

  m_buffer = m_tmpBuffer = 0;

  m_consoleView = new QConsoleView (parent);
  m_scrollBar = new QScrollBar (Qt::Vertical, parent);

  QHBoxLayout* l = new QHBoxLayout (parent);
  l->setContentsMargins (0, 0, 0, 0);
  l->setSpacing (0);
  l->addWidget (m_consoleView, 1);
  l->addWidget (m_scrollBar, 0);

  m_consoleView->setPalette (QPalette (m_backgroundColor));
  m_consoleView->setAutoFillBackground (true);
  m_consoleView->setFont (m_font);
  parent->setFocusPolicy (Qt::StrongFocus);
  parent->winId ();

  updateScrollBar ();

  m_consoleWatcher = new QTimer (parent);
  m_consoleWatcher->setInterval (10);
  m_consoleWatcher->setSingleShot (false);

  QObject::connect (m_scrollBar, SIGNAL (valueChanged (int)),
                    q, SLOT (scrollValueChanged (int)));
  QObject::connect (m_consoleWatcher, SIGNAL (timeout (void)),
                    q, SLOT (monitorConsole (void)));

  m_consoleWatcher->start ();

  if (m_command.isEmpty ())
    m_consoleThread = 0;
  else
    {
      m_consoleThread = new QConsoleThread (q);
      QObject::connect (m_consoleThread, SIGNAL (finished (void)),
                        q, SIGNAL (terminated (void)));
      m_consoleThread->start ();
    }
}