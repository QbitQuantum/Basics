/****************************************************************************
 *
 * NAME: vToggleLed
 *
 * DESCRIPTION:
 * Gets called by a BOS timer. Toggles LED1 to indicate we are alive.
 *
 ****************************************************************************/
PRIVATE void vToggleLed(void *pvMsg, uint8 u8Dummy)
{
    uint8 u8Msg;
    uint8 u8TimerId;
    static int count = 3;
    static bool_t bToggle;
    static int fillcount = 0;
    MAC_ExtAddr_s sExtAddr, *psExtAddr;

    int i;
    AF_Transaction_s asTransaction[1];


    asTransaction[0].u8SequenceNum = u8AfGetTransactionSequence(TRUE);
    asTransaction[0].uFrame.sMsg.u8TransactionDataLen = 1;

    asTransaction[0].uFrame.sMsg.au8TransactionData[0] = 9;
    //static int sensorID[3] = {0, };

    vReadTempHumidity();

    if (bToggle)
    {
        vLedControl(0,0);
    }
    else
    {
        vLedControl(0,1);
    }
    bToggle = !bToggle;
    /* if(afdeDataRequest(APS_ADDRMODE_SHORT,
                          0x0001,
                          WSN_DATA_SOURCE_ENDPOINT,
                          WSN_DATA_SINK_ENDPOINT,
                          WSN_PROFILE_ID,
                          WSN_CID_SENSOR_READINGS,
                          AF_MSG,
                          1,
                          asTransaction,
                          APS_TXOPTION_NONE,
                          SUPPRESS_ROUTE_DISCOVERY,
                          0)){;}
        armCmd = single;*/
    if(commandChanged == TRUE)
    {
        //vPrintf("command changed!\n");
        commandChanged = FALSE;
        switch(armCmd)
        {
            case reflash:
                //vPrintf("reflashed\n");
                sensordata.datatype = WAITING_MODE;
                for(i = 0; i < 6; i++)
                {
                    if(sensordata.sensorinfo[i].isValiable == TRUE)
                    {
                        asTransaction[0].uFrame.sMsg.au8TransactionData[0] = WAITING_MODE;
                        afdeDataRequest(APS_ADDRMODE_SHORT,
                            sensordata.sensorinfo[i].sensorID,
                            WSN_DATA_SOURCE_ENDPOINT,
                            WSN_DATA_SINK_ENDPOINT,
                            WSN_PROFILE_ID,
                            WSN_CID_SENSOR_READINGS,
                            AF_MSG,
                            1,
                            asTransaction,
                            APS_TXOPTION_NONE,
                            SUPPRESS_ROUTE_DISCOVERY,
                            0);
                    }
                }
                break;
            case single:
                //vPrintf("single mode send\n");
                sensordata.sensorID = 0x0001;
                for(i = 0; i < 6; i++)
                {
                    if(sensordata.sensorID != sensordata.sensorinfo[i].sensorID)
                    {
                        if(sensordata.sensorinfo[i].isValiable == TRUE)
                        {
                            sExtAddr.u32L = sensordata.sensorinfo[i].macl;
                            sExtAddr.u32H = sensordata.sensorinfo[i].mach;

                            JZS_vRemoveNode(&sExtAddr, TRUE);
                            //bNwkRemoveDevice(u16AddrSrc);
                            vPrintf("sensor: %d remove success!x\n", sensordata.sensorinfo[i].sensorID);
                            sensordata.sensorinfo[i].isValiable = FALSE;
                        }
                    }
                }
                asTransaction[0].uFrame.sMsg.au8TransactionData[0] = CONTROL_CMD_GET_DATA_S;
                afdeDataRequest(APS_ADDRMODE_SHORT,
                        sensordata.sensorID,
                        WSN_DATA_SOURCE_ENDPOINT,
                        WSN_DATA_SINK_ENDPOINT,
                        WSN_PROFILE_ID,
                        WSN_CID_SENSOR_READINGS,
                        AF_MSG,
                        1,
                        asTransaction,
                        APS_TXOPTION_NONE,
                        SUPPRESS_ROUTE_DISCOVERY,
                        0);
                /*singledata.estate.num++;
                if(singledata.estate.num > 5)
                {
                    singledata.estate.num = 0;
                    singledata.estate.estate = E_FILL_COMPLETE;
                }else
                    singledata.estate.estate = E_FILL_UNCOMPLETE;
                singledata.tempdata[singledata.estate.num] = sTempHumiditySensor.u16TempReading;
                singledata.humidata[singledata.estate.num] = sTempHumiditySensor.u16HumidReading;
                if(singledata.tempdata[singledata.estate.num] > 100)
                {
                    singledata.tempdata[singledata.estate.num] = 100;
                    singledata.templength[singledata.estate.num] = 3;
                }else if(singledata.tempdata[singledata.estate.num] <= 0)
                {
                    singledata.tempdata[singledata.estate.num] = 0;
                    singledata.templength[singledata.estate.num] = 1;
                }else
                {
                    singledata.templength[singledata.estate.num] = 2;
                }

                if(singledata.humidata[singledata.estate.num] > 100)
                {
                    singledata.humidata[singledata.estate.num] = 100;
                    singledata.humilength[singledata.estate.num] = 3;
                }else if(singledata.humidata[singledata.estate.num] <= 0)
                {
                    singledata.humidata[singledata.estate.num] = 0;
                    singledata.humilength[singledata.estate.num] = 1;
                }else
                {
                    singledata.humilength[singledata.estate.num] = 2;
                }

                if(singledata.estate.estate == E_FILL_COMPLETE)
                    vPrintf("S%d,T[%d]%d:%d,H[%d]%d:%d,T[%d]%d:%d,H[%d]%d:%d,T[%d]%d:%d,H[%d]%d:%d,T[%d]%d:%d,H[%d]%d:%d,T[%d]%d:%d,H[%d]%d:%d,T[%d]%d:%d,H[%d]%d:%d\n",
                                singledata.sensorID, 0, singledata.templength[0], singledata.tempdata[0], 0, singledata.humilength[0], singledata.humidata[0],
                                1, singledata.templength[1], singledata.tempdata[1], 1, singledata.humilength[1], singledata.humidata[1],
                                2, singledata.templength[2], singledata.tempdata[2], 2, singledata.humilength[2], singledata.humidata[2],
                                3, singledata.templength[3], singledata.tempdata[3], 3, singledata.humilength[3], singledata.humidata[3],
                                4, singledata.templength[4], singledata.tempdata[4], 4, singledata.humilength[4], singledata.humidata[4],
                                5, singledata.templength[5], singledata.tempdata[5], 5, singledata.humilength[5], singledata.humidata[5]);
                    //vTxSerialDataFrame(1, sTempHumiditySensor.u16HumidReading,sTempHumiditySensor.u16TempReading);
                sTempHumiditySensor.eState = E_STATE_READ_TEMP_HUMID_IDLE;*/
                break;
            case mulit:
                for(i = 0; i < 6; i++)
                {
                    asTransaction[0].uFrame.sMsg.au8TransactionData[0] = CONTROL_CMD_GET_DATA_M;
                    if(sensordata.sensorinfo[i].isValiable == TRUE)
                        afdeDataRequest(APS_ADDRMODE_SHORT,
                        sensordata.sensorinfo[i].sensorID,
                        WSN_DATA_SOURCE_ENDPOINT,
                        WSN_DATA_SINK_ENDPOINT,
                        WSN_PROFILE_ID,
                        WSN_CID_SENSOR_READINGS,
                        AF_MSG,
                        1,
                        asTransaction,
                        APS_TXOPTION_NONE,
                        SUPPRESS_ROUTE_DISCOVERY,
                        0);
                    /*if(multidata[i].available == NOT_NULL)
                    {
                        multidata[i].tempdata = sTempHumiditySensor.u16TempReading;
                        multidata[i].humidata = sTempHumiditySensor.u16HumidReading;
                        vPrintf("S:%d,T:%d,H:%d\n",
                                multidata[i].sensorID, multidata[i].tempdata, multidata[i].humidata);
                    }*/
                }
                //sTempHumiditySensor.eState = E_STATE_READ_TEMP_HUMID_IDLE;
                break;
            case stop:
                //vPrintf("stopped!\n");
                break;
            default:
                    //vPrintf("wait for start!\n");
                break;
        }
    }
    if(sensordata.datatype == WAITING_MODE)
    {
        for(i = 0; i < 6; i++)
        {
            if(sensordata.sensorinfo[i].isValiable == TRUE)
                vPrintf("%d is avaliable x\n", sensordata.sensorinfo[i].sensorID);
        }
    }
    else if(sensordata.datatype == SINGLE_MODE)
    {
        if(fillcount == 6)
            fillcount = 0;

        vPrintf("S%dT%dL%d%dH%dL%d%dx\n", sensordata.data.sd.sensorID,
                                         fillcount, sensordata.data.sd.templength[fillcount], sensordata.data.sd.tempdata[fillcount],
                                         fillcount, sensordata.data.sd.humilength[fillcount], sensordata.data.sd.humidata[fillcount]);
        fillcount++;
    }
    else if(sensordata.datatype == MULTI_MODE)
    {
        for(i = 0; i < 6; i++)
        {
            if(sensordata.data.md[i].isValiable == TRUE)
                vPrintf("S%dT%dL%d%dH%dL%d%dx\n", sensordata.data.md[i].sensorID,
                                                 i, sensordata.data.md[i].templength, sensordata.data.md[i].tempdata,
                                                 i, sensordata.data.md[i].humilength, sensordata.data.md[i].humidata);
        }
    }
    else if(sensordata.datatype == UNSTARTED)
    {
        //vPrintf("wait for start\n");
    }

    (void)bBosCreateTimer(vToggleLed, &u8Msg, 0, (APP_TICK_PERIOD_ms / 10), &u8TimerId);
}