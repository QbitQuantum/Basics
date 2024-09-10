void QSysMessagePanel::addMessage(const QString &from, const QString &msg)
{
    int width = QAppUtils::ref().getScreenWid();
    QMessageWidgets *msgWidget =
            dynamic_cast<QMessageWidgets*> (QWinFactory::ref().createWindow(QWinFactory::MsgWidget,this));

    msgWidget->setMinimumWidth(width/4.2);
    msgWidget->setWindowTitle(from);
    msgWidget->setMessage(msg);
    msgWidget->setAttribute(Qt::WA_TranslucentBackground);
    getLayout()->addWidget(msgWidget,m_currow++,0,1,1,Qt::AlignHCenter);
}