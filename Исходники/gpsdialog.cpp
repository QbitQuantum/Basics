//---------------------------------------------------------------------------
void GPSDialog::gpsDataAvailable(void)
{
    if(gps->isValid()) {
        if(ui->setTimeCb->isChecked()) {
            ui->setTimeCb->setChecked(false);

            bool rc = false;

#ifdef Q_OS_WIN

            SYSTEMTIME st;
            QDateTime  rx_dt = gps->getrxtime(true);
            QDate rx_date    = rx_dt.date();
            QTime rx_time    = rx_dt.time();

            st.wYear         = rx_date.year();
            st.wMonth        = rx_date.month();
            st.wDayOfWeek    = rx_date.dayOfWeek(); // ignored
            st.wDay          = rx_date.day();

            st.wHour         = rx_time.hour();
            st.wMinute       = rx_time.minute();
            st.wSecond       = rx_time.second();
            st.wMilliseconds = rx_time.msec();

            rc = SetSystemTime(&st);

#else // unix

            const time_t tt = gps->rxtime_t();

            if(stime(&tt) == 0)
                rc = true;

#endif // #ifdef Q_OS_WIN

#if defined(DEBUG_GPS)
            if(rc == false)
                qDebug("** Failed to set system time [%s:%d]\n", __FILE__, __LINE__);
            else
                qDebug("** New system time set to GPS time [%s:%d]\n", __FILE__, __LINE__);
#endif

        }

        if(ui->setQTHCB->isChecked()) {
#if 0 // fixme
           ui->setQTHCB->setChecked(false);

           TStation *qth = mw->getQTH();

           qth->lat(gps->latitude_d());
           qth->lon(gps->longitude_d());
           qth->alt(gps->altitude_d());

           mw->updateQTH();
#endif
        }

    } // if(gps->isValid())

    ui->qualityLabel->setText(gps->quality());
    ui->timeLabel->setText(gps->time(!ui->utcTimeCb->isChecked()));
    ui->diffLabel->setText(gps->timediff());
    ui->satsLabel->setText(gps->sats_in_view());
    ui->lonLabel->setText(gps->longitude(ui->dmsCb->isChecked()));
    ui->altLabel->setText(gps->altitude());
    ui->latLabel->setText(gps->latitude(ui->dmsCb->isChecked()));
    ui->speedLabel->setText(gps->speedStr());
    ui->courceLabel->setText(gps->cource());
    ui->geoHeightLabel->setText(gps->mean_sea_level());
    ui->magvarLabel->setText(gps->magnetic());


}