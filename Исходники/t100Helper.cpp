void t100Helper_fillDeviceList(QVector<t100*> &deviceList)
{
    int rval;
    int loopCount;
    int errorCount = 0;

    loopCount = deviceList.size();

    for(int i=0;i<loopCount;i++)
    {
        t100* tmp = deviceList.at(0);

        tmp->disconnect();

        deviceList.remove(0);
    }

    /* Fill the device count in a global array for later disconnect and all. */
    deviceCount = t100_coordinator.searchDevices();    

    for(int i=0;i<deviceCount;i++)
    {
        t100* tmp = createT100();

        tmp->init();

        rval = tmp->connectBySerial(t100_coordinator.getSerialNumber(i));

        if(rval < 0)
        {
            delete tmp;
            errorCount++;
        }
        else
        {            
            /* Default is K thermocouple ... */
            tmp->setThermocoupleType(KType);
            tmp->setPgaGain(8);
            deviceList.append(tmp);
        }                
    }

    deviceCount -= errorCount;
}