void GPSNmea::ProcessGPRMC(uint8_t *pData)
{
    CHAR pBuff[10];
    BYTE pField[MAXFIELD];

    // Time
    if(GetField(pData, pField, 0, MAXFIELD))
    {
        // Hour
        pBuff[0] = pField[0];
        pBuff[1] = pField[1];
        pBuff[2] = '\0';
        data.hours = atoi(pBuff);

        // minute
        pBuff[0] = pField[2];
        pBuff[1] = pField[3];
        pBuff[2] = '\0';
        data.minutes = atoi(pBuff);

        // Second
        pBuff[0] = pField[4];
        pBuff[1] = pField[5];
        pBuff[2] = '\0';
        data.seconds = atoi(pBuff);
    }

    //
    // Data valid
    //
    if(GetField(pData, pField, 1, MAXFIELD)) {
        if(pField[0] == 'A') {
            if(data.altitude > 0)
                data.fixType = data.Fix3D;
            else
                data.fixType = data.Fix2D;
        }
        else
            data.fixType = data.NoFix;
    }

    //
    // latitude
    //
    if(GetField(pData, pField, 2, MAXFIELD))
    {
        data.latitude = lroundf(10000000 * atof((char *) pField + 2) / 60.0);
        pField[2] = '\0';
        data.latitude += lroundf(10000000 * atof((char *) pField));

    }
    if(GetField(pData, pField, 3, MAXFIELD))
    {
        if(pField[0] == 'S')
        {
            data.latitude = -data.latitude;
        }
    }

    //
    // Longitude
    //
    if(GetField(pData, pField, 4, MAXFIELD))
    {
        data.longitude = lroundf(10000000 * atof((CHAR *)pField+3) / 60.0);
        pField[3] = '\0';
        data.longitude += lroundf(10000000 * atof((CHAR *)pField));
    }
    if(GetField(pData, pField, 5, MAXFIELD))
    {
        if(pField[0] == 'W')
        {
            data.longitude = -data.longitude;
        }
    }

    //
    // Ground speed
    //
    if(GetField(pData, pField, 6, MAXFIELD))
    {   // convert to cm/s
        data.speed = lroundf(51.4444 * atof((CHAR *)pField));
    }
    else
    {
        data.speed = 0.0;
    }

    //
    // course over ground, degrees true converted 0.01 degree
    //
    if(GetField(pData, pField, 7, MAXFIELD))
    {
        data.heading = lroundf(100 * atof((CHAR *)pField));
    }
    else
    {
        data.heading = 0.0;
    }

    //
    // Date
    //
    if(GetField(pData, pField, 8, MAXFIELD))
    {
        // Day
        pBuff[0] = pField[0];
        pBuff[1] = pField[1];
        pBuff[2] = '\0';
        data.day = atoi(pBuff);

        // Month
        pBuff[0] = pField[2];
        pBuff[1] = pField[3];
        pBuff[2] = '\0';
        data.month = atoi(pBuff);

        // Year (Only two digits. I wonder why?)
        pBuff[0] = pField[4];
        pBuff[1] = pField[5];
        pBuff[2] = '\0';
        data.year = atoi(pBuff);
        data.year += 2000;             // make 4 digit date
    }
}