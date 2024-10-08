//Calls the Feedback low-level command numIterations times and calculates the
//time per iteration.
int allIO(HANDLE hDevice, u6CalibrationInfo *caliInfo)
{
    uint8 *sendBuff, *recBuff;
    uint16 checksumTotal, bits16;
    uint32 bits32;

    int sendChars, recChars, i, j, sendSize, recSize;
    double valueAIN[14];
    long time;
    int ret = 0;

    for( i = 0; i < 14; i++ )
        valueAIN[i] = 9999;

    //Setting up a Feedback command that will set CIO0-3 as input, and setting
    //DAC0 voltage
    sendBuff = (uint8 *)malloc(18*sizeof(uint8));  //Creating an array of size 18
    recBuff = (uint8 *)malloc(10*sizeof(uint8));   //Creating an array of size 10

    sendBuff[1] = (uint8)(0xF8);  //Command byte
    sendBuff[2] = 6;              //Number of data words (.5 word for echo, 5.5
                                  //words for IOTypes and data)
    sendBuff[3] = (uint8)(0x00);  //Extended command number

    sendBuff[6] = 0;    //Echo
    sendBuff[7] = 29;   //IOType is PortDirWrite
    sendBuff[8] = 0;    //FIO Writemask
    sendBuff[9] = 0;    //EIO Writemask
    sendBuff[10] = 15;  //CIO Writemask
    sendBuff[11] = 0;   //FIO Direction
    sendBuff[12] = 0;   //EIO Direction
    sendBuff[13] = 0;   //CIO Direction

    //Setting DAC0 with 2.5 volt output
    sendBuff[14] = 38;    //IOType is DAC0(16-bit)

    //Value is 2.5 volts (in binary)
    getDacBinVoltCalibrated16Bit(caliInfo, 0, 2.5, &bits16);
    sendBuff[15] = (uint8)(bits16&255);
    sendBuff[16] = (uint8)(bits16/256);

    sendBuff[17] = 0;  //extra padding byte

    extendedChecksum(sendBuff, 18);

    //Sending command to U6
    if( (sendChars = LJUSB_Write(hDevice, sendBuff, 18)) < 18 )
    {
        if(sendChars == 0)
            printf("Feedback (CIO input) error : write failed\n");
        else
            printf("Feedback (CIO input) error : did not write all of the buffer\n");
        ret = -1;
        goto cleanmem;
    }

    //Reading response from U6
    if( (recChars = LJUSB_Read(hDevice, recBuff, 10)) < 10 )
    {
        if( recChars == 0 )
        {
            printf("Feedback (CIO input) error : read failed\n");
            ret = -1;
            goto cleanmem;
        }
        else
            printf("Feedback (CIO input) error : did not read all of the buffer\n");
    }

    checksumTotal = extendedChecksum16(recBuff, 10);
    if( (uint8)((checksumTotal / 256) & 0xff) != recBuff[5] )
    {
        printf("Feedback (CIO input) error : read buffer has bad checksum16(MSB)\n");
        ret = -1;
        goto cleanmem;
    }

    if( (uint8)(checksumTotal & 0xff) != recBuff[4] )
    {
        printf("Feedback (CIO input) error : read buffer has bad checksum16(LBS)\n");
        ret = -1;
        goto cleanmem;
    }

    if( extendedChecksum8(recBuff) != recBuff[0] )
    {
        printf("Feedback (CIO input) error : read buffer has bad checksum8\n");
        ret = -1;
        goto cleanmem;
    }

    if( recBuff[1] != (uint8)(0xF8) || recBuff[3] != (uint8)(0x00) )
    {
        printf("Feedback (CIO input) error : read buffer has wrong command bytes \n");
        ret = -1;
        goto cleanmem;
    }

    if( recBuff[6] != 0 )
    {
        printf("Feedback (CIO input) error : received errorcode %d for frame %d in Feedback response. \n", recBuff[6], recBuff[7]);
        ret = -1;
        goto cleanmem;
    }

    free(sendBuff);
    free(recBuff);

    //Setting up Feedback command that will run numIterations times
    if( ((sendSize = 7+numChannels*4) % 2) != 0 )
        sendSize++; //Need an extra byte
    sendBuff = (uint8 *)malloc(sendSize*sizeof(uint8)); //Creating an array of size sendSize

    if( ((recSize = 9+numChannels*3) % 2) != 0 )
        recSize++;  //Need an extra byte
    recBuff = (uint8 *)malloc(recSize*sizeof(uint8));   //Creating an array of size recSize

    sendBuff[1] = (uint8)(0xF8);     //Command byte
    sendBuff[2] = (sendSize - 6)/2;  //Number of data words
    sendBuff[3] = (uint8)(0x00);     //Extended command number

    sendBuff[6] = 0;     //Echo

    sendBuff[sendSize - 1] = 0;  //Setting last byte to zero in case it is the extra padding byte

    //Setting AIN read commands
    for( j = 0; j < numChannels; j++ )
    {
        sendBuff[7 + j*4] = 2;     //IOType is AIN24

        //Positive Channel (bits 0 - 4), LongSettling (bit 6) and QuickSample (bit 7)
        sendBuff[8 + j*4] = j;  //Positive Channel
        sendBuff[9 + j*4] = (uint8)(resolution&15) + (uint8)((gainIndex&15)*16);   //ResolutionIndex (Bits 0-3), GainIndex (Bits 4-7)
        sendBuff[10 + j*4] = (uint8)(settlingFactor&7);  //SettlingFactor (Bits 0-2)
        if( j%2 == 0 )
            sendBuff[10 + j*4] += (uint8)((differential&1)*128);  //Differential (Bits 7)
    }

    extendedChecksum(sendBuff, sendSize);

    time = getTickCount();

    for( i = 0; i < numIterations; i++ )
    {
        //Sending command to U6
        if( (sendChars = LJUSB_Write(hDevice, sendBuff, sendSize)) < sendSize )
        {
            if(sendChars == 0)
                printf("Feedback error (Iteration %d): write failed\n", i);
            else
                printf("Feedback error (Iteration %d): did not write all of the buffer\n", i);
            ret = -1;
            goto cleanmem;
        }

        //Reading response from U6
        if( (recChars = LJUSB_Read(hDevice, recBuff, recSize)) < recSize )
        {
            if( recChars == 0 )
            {
                printf("Feedback error (Iteration %d): read failed\n", i);
                ret = -1;
                goto cleanmem;
            }
        }

        checksumTotal = extendedChecksum16(recBuff, recChars);
        if( (uint8)((checksumTotal / 256) & 0xff) != recBuff[5] )
        {
            printf("Feedback error (Iteration %d): read buffer has bad checksum16(MSB)\n", i);
            ret = -1;
            goto cleanmem;
        }

        if( (uint8)(checksumTotal & 0xff) != recBuff[4] )
        {
            printf("Feedback error (Iteration %d): read buffer has bad checksum16(LBS)\n", i);
            ret = -1;
            goto cleanmem;
        }

        if( extendedChecksum8(recBuff) != recBuff[0] )
        {
            printf("Feedback error (Iteration %d): read buffer has bad checksum8\n", i);
            ret = -1;
            goto cleanmem;
        }

        if( recBuff[1] != (uint8)(0xF8) || recBuff[3] != (uint8)(0x00) )
        {
            printf("Feedback error (Iteration %d): read buffer has wrong command bytes \n", i);
            ret = -1;
            goto cleanmem;
        }

        if( recBuff[6] != 0 )
        {
            printf("Feedback error (Iteration %d): received errorcode %d for frame %d in Feedback response. \n", i, recBuff[6], recBuff[7]);
            ret = -1;
            goto cleanmem;
        }

        if( recChars != recSize )
        {
            printf("Feedback error (Iteration %d): received packet if %d size when expecting %d\n", i, recChars, recSize);
            ret = -1;
            goto cleanmem;
        }

        //Getting AIN voltages
        for(j = 0; j < numChannels; j++)
        {
            bits32 = recBuff[9+j*3] + recBuff[10+j*3]*256 + recBuff[11+j*3]*65536;
            getAinVoltCalibrated(caliInfo, resolution, gainIndex, 1, bits32, &valueAIN[j]);
        }
    }

    time = getTickCount() - time;
    printf("Milliseconds per iteration = %.3f\n", (double)time / (double)numIterations);
    printf("\nAIN readings from last iteration:\n");

    for( j = 0; j < numChannels; j++ )
        printf("%.3f\n", valueAIN[j]);

cleanmem:
    free(sendBuff);
    free(recBuff);
    sendBuff = NULL;
    recBuff = NULL;

    return ret;
}