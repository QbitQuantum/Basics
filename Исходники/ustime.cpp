QDateTime operator+(const QDateTime &dateTime, const Time &time) {
    int dt = time.time();
    switch (time.unit()) {
    case Time::Seconds:
        return dateTime.addSecs(dt);
    case Time::Minutes:
        return dateTime.addSecs(60*dt);
    case Time::Hours:
        return dateTime.addSecs(60*60*dt);
    case Time::Days:
        return dateTime.addDays(dt);
    case Time::Years:
        QDate date = dateTime.date();
        QTime savedTime = dateTime.time();
        date = QDate(date.year() + dt, date.month(), date.day());
        return QDateTime(date, savedTime, dateTime.timeSpec());
    }
    Q_ASSERT(false);
    return QDateTime();
}