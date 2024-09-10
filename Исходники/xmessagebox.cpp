int XMessageBox::message( QWidget * parent, QMessageBox::Icon severity,
                          const QString & caption, const QString & text,
                          const QString & button0Text,
                          const QString & button1Text,
                          bool snooze, int defaultButtonNumber, int escapeButtonNumber )
{
  QPushButton *button0   = 0;
  QPushButton *button1   = 0;
  QPushButton *buttonsnooze = 0;

  QMessageBox *mb = new QMessageBox(severity, caption, text, QMessageBox::NoButton, parent);
  mb->setObjectName("xtuple_msgbox_snooze");

  Q_CHECK_PTR( mb );

  if (button0Text.isEmpty())
  {
    button0 = mb->addButton(QMessageBox::Ok);
    defaultButtonNumber = snooze ? -1 : 0;
  }
  else
    button0 = mb->addButton(button0Text,
                            defaultButtonNumber == 0 ? QMessageBox::AcceptRole : QMessageBox::RejectRole);

  if (!button1Text.isEmpty())
    button1 = mb->addButton(button1Text,
                            defaultButtonNumber == 1 ? QMessageBox::AcceptRole : QMessageBox::RejectRole);

  if ( snooze )
    buttonsnooze = mb->addButton(QObject::tr("Snooze"), QMessageBox::RejectRole);

  if (defaultButtonNumber == 0)
    mb->setDefaultButton(button0);
  else if (defaultButtonNumber == 1)
    mb->setDefaultButton(button1);
  else if (snooze)
    mb->setDefaultButton(buttonsnooze);

  if (escapeButtonNumber == 0)
    mb->setEscapeButton(button0);
  else if (escapeButtonNumber == 1)
    mb->setEscapeButton(button1);
  else if (snooze)
    mb->setEscapeButton(buttonsnooze);

#ifndef QT_NO_CURSOR
  mb->setCursor(QCursor(Qt::ArrowCursor));
#endif
  int result = -1;
  do {
    QApplication::beep();
    result = mb->exec();
  } while (snooze && mb->clickedButton() == buttonsnooze);

  delete mb;

  return result;
}