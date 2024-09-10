void IQmolApplication::open(QString const& file)
{
   // This is the first thing that is called once the event loop has started,
   // even if there is no actual file to open (empty file name).  This is an
   // ideal time to check if OpenBabel is around.  
   initOpenBabel();

   MainWindow* mw;
   QWidget* window(QApplication::activeWindow());
   if ( !(mw = qobject_cast<MainWindow*>(window)) ) {
      mw = new MainWindow();
      QApplication::setActiveWindow(mw);
   }

   QFileInfo info(file);
   if (info.exists()) mw->openFile(file);
   mw->show();
   mw->raise();

   static bool connected(false);
   if (!connected) {
      connect(this, SIGNAL(lastWindowClosed()), this, SLOT(maybeQuit()));
      connected = true;
   }
   QLOG_INFO() << "Number of threads:" << QThread::idealThreadCount();
   QLOG_INFO() << "Active    threads:" << QThreadPool::globalInstance()->activeThreadCount();
}