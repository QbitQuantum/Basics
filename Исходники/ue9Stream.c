//Reads the StreamData low-level function response in a loop.  All voltages from
//the stream are stored in the voltages 2D array.
int StreamData_example(HANDLE hDevice, ue9CalibrationInfo *caliInfo)
{
    uint16 voltageBytes, checksumTotal;
    int recChars, backLog, overflow;
    int i, j, k, m, packetCounter, currChannel, scanNumber;
    int totalPackets;        //The total number of StreamData responses read
    int numDisplay;          //Number of times to display streaming information
    int numReadsPerDisplay;  //Number of packets to read before displaying streaming information
    int readSizeMultiplier;  //Multiplier for the StreamData receive buffer size
    long startTime, endTime;

    packetCounter = 0;
    currChannel = 0;
    scanNumber = 0;
    totalPackets = 0;
    recChars = 0;
    numDisplay = 6;
    numReadsPerDisplay = 3;
    readSizeMultiplier = 10;

    /* Each StreamData response contains (16/NumChannels) * readSizeMultiplier
     * samples for each channel.
     * Total number of scans = (16 / NumChannels) * 4 * readSizeMultiplier * numReadsPerDisplay * numDisplay
     */
    double voltages[(16/NumChannels)*4*readSizeMultiplier*numReadsPerDisplay*numDisplay][NumChannels];
    uint8 recBuff[192*readSizeMultiplier];

    printf("Reading Samples...\n");

    startTime = getTickCount();

    for( i = 0; i < numDisplay; i++ )
    {
        for( j = 0; j < numReadsPerDisplay; j++ )
        {
            /* For USB StreamData, use Endpoint 2 for reads and 192 byte packets
             * instead of the 46.  The 192 byte response is 4 StreamData packet
             * responses of 48 bytes.
             * You can read the multiple StreamData responses of 192 bytes to help
             * improve streaming performance.  In this example this multiple is
             * adjusted by the readSizeMultiplier variable.
             */

            //Reading response from UE9
            recChars = LJUSB_Stream(hDevice, recBuff, 192*readSizeMultiplier);
            if( recChars < 192*readSizeMultiplier )
            {
                if( recChars == 0 )
                    printf("Error : read failed (StreamData).\n");
                else
                    printf("Error : did not read all of the buffer %d (StreamData).\n", recChars);
                return -1;
            }

            overflow = 0;

            //Checking for errors and getting data out of each StreamData response
            for( m = 0; m < 4*readSizeMultiplier; m++ )
            {
                totalPackets++;
                checksumTotal = extendedChecksum16(recBuff + m*48, 46);
                if( (uint8)((checksumTotal >> 8) & 0xff) != recBuff[m*48 + 5] )
                {
                    printf("Error : read buffer has bad checksum16(MSB) (StreamData).\n");
                    return -1;
                }

                if( (uint8)(checksumTotal & 0xff) != recBuff[m*48 + 4] )
                {
                    printf("Error : read buffer has bad checksum16(LSB) (StreamData).\n");
                    return -1;
                }

                checksumTotal = extendedChecksum8(recBuff + m*48);
                if( checksumTotal != recBuff[m*48] )
                {
                    printf("Error : read buffer has bad checksum8 (StreamData).\n");
                    return -1;
                }

                if( recBuff[m*48 + 1] != (uint8)(0xF9) || recBuff[m*48 + 2] != (uint8)(0x14) || recBuff[m*48 + 3] != (uint8)(0xC0) )
                {
                    printf("Error : read buffer has wrong command bytes (StreamData).\n");
                    return -1;
                }

                if( recBuff[m*48 + 11] != 0 )
                {
                    printf("Errorcode # %d from StreamData read.\n", (unsigned int)recBuff[11]);
                    return -1;
                }

                if( packetCounter != (int) recBuff[m*48 + 10] )
                {
                    printf("PacketCounter does not match with with current packet count (StreamData).\n");
                    return -1;
                }

                backLog = recBuff[m*48 + 45]&0x7F;

                //Checking MSB for Comm buffer overflow
                if( (recBuff[m*48 + 45] & 128) == 128 )
                {
                    printf("\nComm buffer overflow detected in packet %d\n", totalPackets);
                    printf("Current Comm backlog: %d\n", recBuff[m*48 + 45]&0x7F);
                    overflow = 1;
                }

                for( k = 12; k < 43; k += 2 )
                {
                    voltageBytes = (uint16)recBuff[m*48 + k] + (uint16)recBuff[m*48 + k+1]*256;
                    getAinVoltCalibrated(caliInfo, (uint8)(0x00), ainResolution, voltageBytes, &(voltages[scanNumber][currChannel]));
                    currChannel++;
                    if( currChannel > 3 )
                    {
                        currChannel = 0;
                        scanNumber++;
                    }
                }

                if( packetCounter >= 255 )
                    packetCounter = 0;
                else
                    packetCounter++;

                //Handle Comm buffer overflow by stopping, flushing and restarting stream
                if( overflow == 1 )
                {
                    printf("\nRestarting stream...\n");
                    doFlush(hDevice);
                    if( StreamConfig_example(hDevice) != 0 )
                    {
                        printf("Error restarting StreamConfig.\n");
                        return -1;
                    }

                    if( StreamStart(hDevice) != 0 )
                    {
                        printf("Error restarting StreamStart.\n");
                        return -1;
                    }
                    packetCounter = 0;
                    break;
                }
            }
        }

        printf("\nNumber of scans: %d\n", scanNumber);
        printf("Total packets read: %d\n", totalPackets);
        printf("Current PacketCounter: %d\n", ((packetCounter == 0) ? 255 : packetCounter-1));
        printf("Current Comm backlog: %d\n", backLog);

        for( k = 0; k < 4; k++ )
            printf("  AI%d: %.4f V\n", k, voltages[scanNumber - 1][k]);
    }

    endTime = getTickCount();
    printf("\nRate of samples: %.0lf samples per second\n", (scanNumber*NumChannels)/((endTime - startTime)/1000.0));
    printf("Rate of scans: %.0lf scans per second\n\n", scanNumber/((endTime - startTime)/1000.0));

    return 0;
}