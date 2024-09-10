void SetSystemTimeDialog::onSetSystemTime()
{
    qDebug()<<"设置系统时间";
   SYSTEMTIME st;
   GetSystemTime(&st);
  // qDebug()<<st.wYear<<st.wMonth<<st.wDay<<st.wHour<<st.wMinute<<st.wSecond;
   QDateTime tempdatetime;
   tempdatetime.setDate(ui->dateEdit->date());
   tempdatetime.setTime(ui->timeEdit->time());
   QDateTime datetime = tempdatetime.addSecs(-8*60*60);
   qDebug()<<"datetime"<<datetime;
   st.wYear = datetime.date().year();
   st.wMonth= datetime.date().month();
   st.wDay = datetime.date().day();
   st.wHour = datetime.time().hour();
   st.wMinute = datetime.time().minute();
   st.wSecond = datetime.time().second();
  // qDebug()<<st.wYear<<st.wMonth<<st.wDay<<st.wHour<<st.wMinute<<st.wSecond;
   qDebug()<<"SetSystemTime(&st)"<<SetSystemTime(&st);
   qDebug()<<datetime.date().year()<<datetime.date().month()<<datetime.date().day()<<datetime.time().hour()<<datetime.time().minute()<<datetime.time().second();
   this->accept();
}