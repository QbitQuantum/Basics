int isObjectDetected(void){
	
	int reDist;
	volatile int i;
#ifdef	DISTANCE_DEBUG
	char buf[7];
#endif
	//get distance : AEB	
	distance[0]=sonarGetDistance();
	
#ifdef USE_PIR_SENSOR
	for(i=1;i<3;i++){
		distance[i] = getDistance(i-1);	
	}
#endif
#ifdef	DISTANCE_DEBUG
	for(i=0;i<3;i++){
		intToChar(distance[i],7,buf);
		TransmitData(buf);
		TransmitData("-");
	}
	TransmitData("\r\n");
#endif
		
	if(distance[0]<160){
		reDist = distance[0];
	}else{
		reDist=OBJECT_NOT_DETECTED;
		
#ifdef USE_PIR_SENSOR
		if((distance[1]<65)){
			reDist = distance[1];
		}else{
			if(distance[2]<65){
				reDist = distance[2];
			}else{
				reDist=OBJECT_NOT_DETECTED;	
			}
		}
#endif		
	}
	return reDist;
}