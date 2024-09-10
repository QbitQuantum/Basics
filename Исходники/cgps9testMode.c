void CGPS9_00HandleEvents(t_CgpsEventInformation* pp_EventInfo)
{
    uint8_t   vl_CharactersWritten = 0;
    uint8_t   vl_CheckSum          = 0;
    char vl_NmeaBuffer[K_CGPS_MAX_NMEA_SIZE];
    /*++  For adding newline at the end of PSTE messages */
    char vl_PsteBuffer[K_CGPS_MAX_NMEA_SIZE];
    /*--  For adding newline at the end of PSTE messages */

/* + LMSQC19754 */
    /*The transview tool expects the PSTE messages to have a timestamp that is in resolution of 4ms*/
    uint32_t  vl_timer             = (uint32_t)GN_GPS_Get_OS_Time_ms() / 4;
/*    uint32_t  vl_timer             = GN_GPS_Get_OS_Time_ms(); */
/* - LMSQC19754 */

    vl_CharactersWritten = snprintf(vl_NmeaBuffer, K_CGPS_MAX_NMEA_SIZE, "$PSTE,");

    switch( pp_EventInfo->v_EventType )
    {
        case K_CGPS_RESPONSE_RETURNED:
            vl_CharactersWritten += MC_CGPS_ADD_PSTE_TYPE(vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten, 4);  /* Pste type */
            vl_CharactersWritten += MC_CGPS_ADD_OS_TIME  (vl_NmeaBuffer+vl_CharactersWritten, vl_timer, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);                /*OS time*/
            vl_CharactersWritten += MC_CGPS_ADD_SEPERATOR(vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);                          /* , */
            vl_CharactersWritten += MC_CGPS_ADD_LATLON(vl_NmeaBuffer+vl_CharactersWritten, pp_EventInfo->v_Latitude, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);/*Latitude*/
            vl_CharactersWritten += MC_CGPS_ADD_SEPERATOR(vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);                          /* , */
            vl_CharactersWritten += MC_CGPS_ADD_LATLON  (vl_NmeaBuffer+vl_CharactersWritten, pp_EventInfo->v_Longitude, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);/*Longitude*/
            vl_CharactersWritten += MC_CGPS_ADD_SEPERATOR(vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);                          /* , */
            vl_CharactersWritten += MC_CGPS_ADD_ALT  (vl_NmeaBuffer+vl_CharactersWritten, pp_EventInfo->v_Altitude, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);/*Altitude*/
            vl_CharactersWritten += MC_CGPS_ADD_EOM      (vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);                          /* * */
        break;

        case K_CGPS_POSITIONING_SESSION_START:
            vl_CharactersWritten += MC_CGPS_ADD_PSTE_TYPE(vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten, 1);
            vl_CharactersWritten += MC_CGPS_ADD_OS_TIME  (vl_NmeaBuffer+vl_CharactersWritten, vl_timer, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);
            vl_CharactersWritten += MC_CGPS_ADD_EOM      (vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);
        break;

        case K_CGPS_POSITIONING_SESSION_END:
            vl_CharactersWritten += MC_CGPS_ADD_PSTE_TYPE(vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten, 2);
            vl_CharactersWritten += MC_CGPS_ADD_OS_TIME  (vl_NmeaBuffer+vl_CharactersWritten, vl_timer, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);
            vl_CharactersWritten += MC_CGPS_ADD_EOM      (vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);
        break;

/* + LMSQC19754 */
        case K_CGPS_ABORT_SESSION:
            vl_CharactersWritten += MC_CGPS_ADD_PSTE_TYPE(vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten, 3);
            vl_CharactersWritten += MC_CGPS_ADD_OS_TIME  (vl_NmeaBuffer+vl_CharactersWritten, vl_timer, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);
            vl_CharactersWritten += MC_CGPS_ADD_EOM      (vl_NmeaBuffer+vl_CharactersWritten, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);
        break;
/* - LMSQC19754 */

        default:
        break;
    }

    vl_CheckSum = CGPS9_01GenerateCheckSum(vl_NmeaBuffer, strlen((const char*)vl_NmeaBuffer));

    vl_CharactersWritten += MC_CGPS_ADD_CS (vl_NmeaBuffer+vl_CharactersWritten, vl_CheckSum, K_CGPS_MAX_NMEA_SIZE-vl_CharactersWritten);

    MC_CGPS_TRACE(("%s", vl_NmeaBuffer));

    sprintf(vl_PsteBuffer,"%s\r\n",vl_NmeaBuffer);
/*--  For adding newline at the end of PSTE messages */
    if( vg_CgpsTestall.p_Callback != NULL  )
    {
        t_cgps_NavData vl_NavDataToSend;

        vl_NavDataToSend.v_Type    = K_CGPS_NMEA;
        vl_NavDataToSend.v_Length  = vl_CharactersWritten;
        vl_NavDataToSend.p_NavData = vl_NmeaBuffer;
        /*++  For adding newline at the end of PSTE messages */
        sprintf(vl_PsteBuffer,"%s\r\n",vl_NavDataToSend.p_NavData);
        vl_NavDataToSend.v_Length  += 2;
        vl_NavDataToSend.p_NavData = vl_PsteBuffer;
        MC_CGPS_TRACE(("In CGPS9_00HandleEvents calling p_Callback"));

        (vg_CgpsTestall.p_Callback)( vl_NavDataToSend );
    /*--  For adding newline at the end of PSTE messages */
    }
    /* + DUR 19 Jan 2011 NMEA Logging */
       CGPS4_11SendAcknowledge(vl_PsteBuffer);
    /* - DUR 19 Jan 2011 NMEA Logging */
}