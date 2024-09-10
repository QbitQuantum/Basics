void parseifinfo(int newdb)
{
    uint64_t rxchange=0, txchange=0, btime, cc;   /* rxchange = rx change in MB */
    uint64_t krxchange=0, ktxchange=0, maxtransfer;   /* krxchange = rx change in kB */
    time_t current, interval;
    struct tm *d;
    int day, month, year, hour, min, shift, maxbw;
    int rxkchange=0, txkchange=0;			          /* changes in the kB counters */

    ifinfo.rxp = ifinfo.txp = 0;
    current=time(NULL);
    interval=current-data.lastupdated;
    btime=getbtime();

    /* count traffic only if previous update wasn't too long ago */
    if ( interval < (60*MAXUPDATEINTERVAL) ) {

        /* btime in /proc/stat seems to vary ±1 second so we use btime-BVAR just to be safe */
        /* the variation is also slightly different between various kernels... */
        if (data.btime < (btime-cfg.bvar)) {
            data.currx=0;
            data.curtx=0;
            if (debug)
                printf("System has been booted.\n");
        }

        /* process rx & tx */
        if (newdb!=1) {
            cc = countercalc(&data.currx, &ifinfo.rx);
            rxchange = cc/1048576;      /* 1024/1024 */
            rxkchange = (cc/1024)%1024;
            krxchange = cc/1024;
            ifinfo.rxp = cc%1024;

            cc = countercalc(&data.curtx, &ifinfo.tx);
            txchange = cc/1048576;      /* 1024/1024 */
            txkchange = (cc/1024)%1024;
            ktxchange = cc/1024;
            ifinfo.txp = cc%1024;
        }

        /* get bandwidth limit for current interface */
        maxbw = ibwget(data.interface);

        if (maxbw > 0) {

            /* calculate maximum possible transfer since last update based on set maximum rate */
            /* and add 10% in order to be on the safe side */
            maxtransfer = ceil((maxbw/(float)8)*interval*(float)1.1);

            if (debug)
                printf("interval: %"PRIu64"  maxbw: %d  maxrate: %"PRIu64"  rxc: %"PRIu64"  txc: %"PRIu64"\n", (uint64_t)interval, maxbw, maxtransfer, rxchange, txchange);

            /* sync counters if traffic is greater than set maximum */
            if ( (rxchange > maxtransfer) || (txchange > maxtransfer) ) {
                snprintf(errorstring, 512, "Traffic rate for \"%s\" higher than set maximum %d Mbit (%"PRIu64"->%"PRIu64", r%"PRIu64" t%"PRIu64"), syncing.", data.interface, maxbw, (uint64_t)interval, maxtransfer, rxchange, txchange);
                printe(PT_Info);
                rxchange = krxchange = rxkchange = txchange = ktxchange = txkchange = 0;
                ifinfo.rxp = ifinfo.txp = 0;
            }
        }

    } else {
        if (debug)
            printf("Too much time passed since previous update, syncing. (%"PRIu64" < %d)\n", (uint64_t)interval, 60*MAXUPDATEINTERVAL);
    }


    /* keep btime updated in case it drifts slowly */
    data.btime = btime;

    data.currx = ifinfo.rx - ifinfo.rxp;
    data.curtx = ifinfo.tx - ifinfo.txp;
    addtraffic(&data.totalrx, &data.totalrxk, rxchange, rxkchange);
    addtraffic(&data.totaltx, &data.totaltxk, txchange, txkchange);

    /* update days and months */
    addtraffic(&data.day[0].rx, &data.day[0].rxk, rxchange, rxkchange);
    addtraffic(&data.day[0].tx, &data.day[0].txk, txchange, txkchange);
    addtraffic(&data.month[0].rx, &data.month[0].rxk, rxchange, rxkchange);
    addtraffic(&data.month[0].tx, &data.month[0].txk, txchange, txkchange);

    /* fill some variables from current date & time */
    d=localtime(&current);
    if (d==NULL) {
        panicexit(__FILE__, __LINE__);
    }
    day=d->tm_mday;
    month=d->tm_mon;
    year=d->tm_year;
    hour=d->tm_hour;
    min=d->tm_min;
    shift=hour;

    /* add traffic to previous hour when update happens at X:00 */
    /* and previous update was during previous hour */
    d=localtime(&data.lastupdated);
    if (d==NULL) {
        panicexit(__FILE__, __LINE__);
    }
    if ((min==0) && (d->tm_hour!=hour) && ((current-data.lastupdated)<=3600)) {
        hour--;
        if (hour<0) {
            hour=23;
        }
    }

    /* clean and update hourly */
    cleanhours();
    data.hour[shift].date=current;   /* avoid shifting timestamp */
    data.hour[hour].rx+=krxchange;
    data.hour[hour].tx+=ktxchange;

    /* rotate days in database if needed */
    d=localtime(&data.day[0].date);
    if (d==NULL) {
        panicexit(__FILE__, __LINE__);
    }
    if ((d->tm_mday!=day) || (d->tm_mon!=month) || (d->tm_year!=year)) {

        /* make a new entry only if there's something to remember (configuration dependent) */
        if ( (data.day[0].rx==0) && (data.day[0].tx==0) && (data.day[0].rxk==0) && (data.day[0].txk==0) && (cfg.traflessday==0) ) {
            data.day[0].date=current;
        } else {
            rotatedays();
        }
    }

    /* rotate months in database if needed */
    d=localtime(&data.month[0].month);
    if (d==NULL) {
        panicexit(__FILE__, __LINE__);
    }
    if ((d->tm_mon!=month) && (day>=cfg.monthrotate)) {
        rotatemonths();
    }
}