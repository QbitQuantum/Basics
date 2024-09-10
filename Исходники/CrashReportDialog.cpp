/*!
 * \brief CrashReportDialog::sendReport
 * Slot activated when mpSendReportButton clicked signal is raised.\n
 * Sends the crash report alongwith selected log files.
 */
void CrashReportDialog::sendReport()
{
  // ask for e-mail address.
  if (mpEmailTextBox->text().isEmpty()) {
    QMessageBox *pMessageBox = new QMessageBox;
    pMessageBox->setWindowTitle(QString(Helper::applicationName).append(" - ").append(Helper::error));
    pMessageBox->setIcon(QMessageBox::Critical);
    pMessageBox->setAttribute(Qt::WA_DeleteOnClose);
    pMessageBox->setText(tr("We can't contact you with a possible solution if you don't provide a valid e-mail address."));
    pMessageBox->addButton(tr("Send without e-mail"), QMessageBox::AcceptRole);
    pMessageBox->addButton(tr("Let me enter e-mail"), QMessageBox::RejectRole);
    int answer = pMessageBox->exec();
    switch (answer) {
      case QMessageBox::RejectRole:
        mpEmailTextBox->setFocus();
        return;
      case QMessageBox::AcceptRole:
      default:
        break;
    }
  }
  // create the report.
  QHttpMultiPart *pHttpMultiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  // email
  QHttpPart emailHttpPart;
  emailHttpPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"email\""));
  emailHttpPart.setBody(mpEmailTextBox->text().toUtf8());
  pHttpMultiPart->append(emailHttpPart);
  // bug description
  QHttpPart bugDescriptionHttpPart;
  bugDescriptionHttpPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"bugdescription\""));
  bugDescriptionHttpPart.setBody(mpBugDescriptionTextBox->toPlainText().toUtf8());
  pHttpMultiPart->append(bugDescriptionHttpPart);
  // OMEditCommunicationLogFile
  if (mpOMEditCommunicationLogFileCheckBox->isChecked()) {
    QHttpPart OMEditCommunicationLogFileHttpPart;
    OMEditCommunicationLogFileHttpPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    OMEditCommunicationLogFileHttpPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"omeditcommunication.log\"; filename=\"omeditcommunication.log\""));
    QFile *pOMEditCommunicationLogFileFile = new QFile(mpOMEditCommunicationLogFileCheckBox->text());
    pOMEditCommunicationLogFileFile->open(QIODevice::ReadOnly);
    OMEditCommunicationLogFileHttpPart.setBodyDevice(pOMEditCommunicationLogFileFile);
    pOMEditCommunicationLogFileFile->setParent(pHttpMultiPart); // file will be deleted when we delete pHttpMultiPart
    pHttpMultiPart->append(OMEditCommunicationLogFileHttpPart);
  }
  // OMEditCommandsMosFile
  if (mpOMEditCommandsMosFileCheckBox->isChecked()) {
    QHttpPart OMEditCommandsMosFileHttpPart;
    OMEditCommandsMosFileHttpPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    OMEditCommandsMosFileHttpPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"omeditcommands.mos\"; filename=\"omeditcommands.mos\""));
    QFile *pOMEditCommandsMosFile = new QFile(mpOMEditCommandsMosFileCheckBox->text());
    pOMEditCommandsMosFile->open(QIODevice::ReadOnly);
    OMEditCommandsMosFileHttpPart.setBodyDevice(pOMEditCommandsMosFile);
    pOMEditCommandsMosFile->setParent(pHttpMultiPart); // file will be deleted when we delete pHttpMultiPart
    pHttpMultiPart->append(OMEditCommandsMosFileHttpPart);
  }
  // OMStackTraceFile
  if (mpOMStackTraceFileCheckBox->isChecked()) {
    QHttpPart OMStackTraceFileCheckBoxHttpPart;
    OMStackTraceFileCheckBoxHttpPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    OMStackTraceFileCheckBoxHttpPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"openmodelica.stacktrace.OMEdit\"; filename=\"openmodelica.stacktrace.OMEdit\""));
    QFile *pOMStackTraceFile = new QFile(mpOMStackTraceFileCheckBox->text());
    pOMStackTraceFile->open(QIODevice::ReadOnly);
    OMStackTraceFileCheckBoxHttpPart.setBodyDevice(pOMStackTraceFile);
    pOMStackTraceFile->setParent(pHttpMultiPart); // file will be deleted when we delete pHttpMultiPart
    pHttpMultiPart->append(OMStackTraceFileCheckBoxHttpPart);
  }
  // create the request
  QUrl url("https://dev.openmodelica.org/omeditcrashreports/cgi-bin/server.py");
  QNetworkRequest networkRequest(url);
  QNetworkAccessManager *pNetworkAccessManager = new QNetworkAccessManager;
  QNetworkReply *pNetworkReply = pNetworkAccessManager->post(networkRequest, pHttpMultiPart);
  pNetworkReply->ignoreSslErrors();
  pHttpMultiPart->setParent(pNetworkReply); // delete the pHttpMultiPart with the pNetworkReply
  connect(pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), SLOT(reportSent(QNetworkReply*)));
}