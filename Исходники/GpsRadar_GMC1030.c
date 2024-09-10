void GPSRadar_SetCommand_GMC1030(RADARSET_TYPE ubType, MMP_UBYTE ubValue)
{
	MMP_BYTE chCommand[15];
	MMP_BYTE chTempBuffer[2];
	MMP_UBYTE ubXorTemp =0, i;

	MEMSET(chCommand, 0, 15);
	MEMSET(chTempBuffer, 0, 2);
	STRCAT(chCommand, "$2,");
	
	//Command Type.
	if(ubType <10)
	STRCAT(chCommand, "0");
	sprintf(chTempBuffer, "%d",ubType);
	STRCAT(chCommand, chTempBuffer);
	
	STRCAT(chCommand, ":");
	
	//Command Value
	if(ubValue <10)
	STRCAT(chCommand, "0");
	sprintf(chTempBuffer, "%d",ubValue);
	STRCAT(chCommand, chTempBuffer);
	
	STRCAT(chCommand, "*");
	
	//Checksum
	for(i = 1; i<8; i++) //Between $ to *
	ubXorTemp ^= chCommand[i];	
	sprintf(chTempBuffer, "%x",ubXorTemp);
	STRCAT(chCommand ,chTempBuffer);
	
	//Tail
	STRCAT(chCommand, "\r\n");
	printc("chCommand : %s\r\n",chCommand);
	
	//Write fixed-length(13) ASCII codes to Radar
	MMPF_Uart_Write(GPSRADAR_UART_NUM, chCommand, 13 );
		
}