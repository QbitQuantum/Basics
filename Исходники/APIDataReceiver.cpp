void APIDataReceiver::run()
{
    timeBeginPeriod(1);
    int lastUpdate = -1;

    while(!stop)
    {
        // wait for new data and copy it into the data buffer, if data is not null
        if(waitForDataReady(TIMEOUT, data))
        {
            if(header)
            {

                // if header changes size, assume a new connection
                if(!data || dataSize != header->bufLen)
                {
                    reset();
                    dataSize = header->bufLen;
                    data = new char[dataSize];
                }
                else if(data)
                {
                    if(lastUpdate < header->sessionInfoUpdate)
                    {
                        updateStaticInfo();
                        //TODO: update semi-static data
                        lastUpdate = header->sessionInfoUpdate;
                    }

                    //TODO: update dynamic data
                }
            }
        }
        else if(!isConnected()) { // session ended
            reset();
        }
    }

    reset();
    shutdown();
    timeEndPeriod(1);
}