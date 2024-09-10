HTTPAPI_RESULT HTTPAPI_Init(void)
{
    LogInfo("HTTPAPI_Init::Start\r\n");
    time_t ctTime;
    ctTime = time(NULL);
    HTTPAPI_RESULT result;
    LogInfo("HTTAPI_Init::Time is now (UTC) %s\r\n", ctime(&ctTime));
    if (eth.init())
    {
        LogInfo("HTTPAPI_Init::Error with initing the Ethernet Interface\r\n");
        result = HTTPAPI_INIT_FAILED;
    }
    else
    {
        LogInfo("HTTPAPI_Init::Ethernet interface was inited!\r\n");
        if (eth.connect(30000))
        {
            LogError("HTTPAPI_Init::Error with connecting.\r\n");
            result = HTTPAPI_INIT_FAILED;
        }
        else
        {
            LogInfo("HTTAPI_Init::Ethernet interface was connected (brought up)!\r\n");
            LogInfo("HTTAPI_Init::MAC address %s\r\n", eth.getMACAddress());
            LogInfo("HTTAPI_Init::IP address %s\r\n", eth.getIPAddress());
            if (ntp.setTime("0.pool.ntp.org") == 0)
            {
                LogInfo("HTTAPI_Init:: Successfully set time\r\n");
                LogInfo("HTTAPI_Init::Time is now (UTC) %s\r\n", ctime(&ctTime));
                result = HTTPAPI_OK;
            }
            else
            {
                LogError("HTTPAPI_INIT::Unable to set time.  Init failed");
                result = HTTPAPI_INIT_FAILED;
            }
        }
    }
    LogInfo("HTTPAPI_Init::End\r\n");
    return result;
}