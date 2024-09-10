void initGPS(void){
	float x=0;
	float dist = 0;

	strCpy(gps_UTCPos,"-",10);
	strCpy(gps_Latitude,"-",9);
	strCpy(gps_NSind,"-",1);
	strCpy(gps_Longitude,"-",10);
	strCpy(gps_EWind,"-",1);
	strCpy(gps_PosFixInd,"-",1);
	strCpy(gps_SatUsed,"-",2);
	strCpy(gps_HDOP,"-",16);
	strCpy(gps_Altitude,"-",16);
	strCpy(gps_AltUnit,"-",16);

	strCpy(gps_Status,"-",1);
	strCpy(gps_SpeedOverGround,"-",16);
	strCpy(gps_CourseOverGround,"-",16);
	strCpy(gps_Date,"-",6);

	iBuff0 = 0;
	iBuff1 = 0;
	useBuffer = 0;
	lengthWaitBuffer = 0;

	destination = 0;
	coordConv(destCoord,"4713,0000","N","00133,0000","W");   // Nantes
	coordConv(destCoord+1,"4313,9450","N","00526,6233","E"); // Polytech luminy
/*	coordConv(destCoord+2,"4314,9500","N","00526,9633","E"); // Vaufrege*/
	coordConv(destCoord+2,"4422,0000","N","00856,0000","E"); // Genova
/*	coordConv(destCoord+3,"4313,6316","N","00526,3333","E"); // Crous*/
	coordConv(destCoord+3,"4122,0000","N","00211,0000","E"); // Barcelone

	setENABLE_GPS(1);
	initTimer_A();
	setFuncTimer_A(&vidageBuffer);
	setTimer_A(1);

	setFuncRx0(&RxBuff0);
	connectGPS(1);

/*	dist = distance(destCoord+1, destCoord+1);

	// Nantes -> Marseille 		128
	dist = distance(destCoord, destCoord+1);
	x = cap2(destCoord, destCoord+1,dist);
	
	// Genova -> Marseille		246
	dist = distance(destCoord+2, destCoord+1);
	x = cap2(destCoord+2, destCoord+1,dist);

	// Barcelone -> Marseille	51
	dist = distance(destCoord+3, destCoord+1);
	x = cap2(destCoord+3, destCoord+1,dist);

	// Marseille -> Nantes		311
	dist = distance(destCoord+1, destCoord);
	x = cap2(destCoord+1, destCoord,dist);

	x++;*/
}