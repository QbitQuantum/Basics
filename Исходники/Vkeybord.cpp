void Vkeybord::slotEnter()
{
    m_lbWaitKeyIn->setText(ui->lineEdit->text());
    qDebug()<<"parent name : "<<m_lbWaitKeyIn->parent()->objectName()<<" ,lb objname : "<<m_lbWaitKeyIn->objectName()<<" lbText: "<<m_lbWaitKeyIn->text();

    ui->lineEdit->setText("");
    m_ani->setStartValue(QPoint(0,0));
    m_ani->setEndValue(QPoint(0,height()));

    QEventLoop loop;
    loop.connect(m_ani,SIGNAL(finished()),&loop,SLOT(quit()));
    m_ani->start();
    loop.exec();
    hide();

    loop.disconnect();
}