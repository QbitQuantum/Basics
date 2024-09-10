void NotifyProvider::LogEventL(const CLogEvent &event)
{
    // store new call
    QString number=QString::fromRawData(reinterpret_cast<const QChar*>(event.Number().Ptr()),event.Number().Length());
    QString direction=QString::fromRawData(reinterpret_cast<const QChar*>(event.Direction().Ptr()),event.Direction().Length());
    QString description=QString::fromRawData(reinterpret_cast<const QChar*>(event.Description().Ptr()),event.Description().Length());
    if (description.contains("Voice call")&&direction.contains("Missed call"))
    {
        TTime times=event.Time();
        RTz tzsession;
        tzsession.Connect();
        tzsession.ConvertToLocalTime(times);
        tzsession.Close();
        TDateTime dts=times.DateTime();
        QDate d; QTime t;
        d.setYMD(dts.Year(),dts.Month()+1,dts.Day()+1);
        t.setHMS(dts.Hour(),dts.Minute(),dts.Second());
        QDateTime dt; dt.setDate(d); dt.setTime(t);
        dt=dt.toLocalTime();
        QString time=dt.toString("d.M.yy hh:mm");

        TNotifyInfo info;
        info.time=time;
        info.timeStamp=dt;
        info.sender=number;
        info.text=findContact(number);
        info.id=-1;
        info.type=EMissedCall;
        iNotifiers.insert(0,info);
        qDebug()<<"store call from"<<info.sender;
        prepareNotifier(EMissedCall);
    }
}