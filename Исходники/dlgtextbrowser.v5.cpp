dlgTextBrowser::dlgTextBrowser(const char *manual)
{
  char cmd[1024],buf[1024];

  homeIsSet = 0;
  strcpy(buf,"index.html");
  
  form = new Ui_DialogTextBrowser;
  form->setupUi(this);
#ifndef USE_ANDROID
  form->textBrowser->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
#endif

  if(manual == NULL)
  {
    setWindowTitle(tr("pvbrowser Manual"));
  }
  else
  {
    if(strlen(manual) < (int) (sizeof(cmd)-1) ) strcpy(buf,manual);
  }

#ifdef PVWIN32
  ExpandEnvironmentStringsA(buf,cmd,sizeof(cmd)-1);
#else
  strcpy(cmd,buf);
#endif

  QFile fin(cmd);
  if(fin.exists())
  {
    // this is damn slow on windows begin
#ifdef PVDEVELOP
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#ifdef USE_ANDROID
    form->textBrowser->setSource(QUrl::fromLocalFile(cmd));
#else
    form->textBrowser->load(QUrl::fromLocalFile(cmd));
#endif    
    QApplication::restoreOverrideCursor();
#endif
    // this is damn slow on windows end
    home = cmd;
    homeIsSet = 1;
  }
  else
  {
    form->textBrowser->setHtml("<html><head></head><body>Sorry no application specific help specified.</body></html>");
  }

  QObject::connect(form->pushButtonFind,SIGNAL(clicked()),this,SLOT(slotFind()));
  QObject::connect(form->lineEditPattern,SIGNAL(returnPressed()),this,SLOT(slotFind()));
  QObject::connect(form->pushButtonClose,SIGNAL(clicked()),this,SLOT(hide()));
  QObject::connect(form->pushButtonHome,SIGNAL(clicked()),this,SLOT(slotHome()));
  QObject::connect(form->pushButtonBack,SIGNAL(clicked()),this,SLOT(slotBack()));
  find = 0;
}