/** Main application
 *
 * @param argc :: ignored
 * @param argv :: ignored
 * @return return code
 */
int main( int argc, char ** argv )
{
  double min=0;
  double max=100;

  QApplication app(argc, argv);
  app.setOrganizationName("MantidProject");
  app.setApplicationName("Color Bar Widget Example");
  QMainWindow * mainWin = new QMainWindow();

  QFrame * frame = new QFrame(mainWin);
  mainWin->setCentralWidget(frame);

  QLayout * layout = new QVBoxLayout(frame);
  frame->setLayout(layout);

  ColorBarWidget * widget = new ColorBarWidget(frame);

  widget->setViewRange(min, max);
  widget->setLog(false);

  layout->addWidget(widget);
  mainWin->move(100, 100);
  mainWin->resize(40, 500);
  mainWin->show();

  app.exec();

  mainWin->close();
  delete mainWin;
  return 0;
}