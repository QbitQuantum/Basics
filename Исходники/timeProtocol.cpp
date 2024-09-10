	}
	return a;
}
void resetSofftwareCorrection(void){

		sumOffset.second=0;
		sumOffset.halfmillis=0;
		timeProt.correction.nbCorrection=0;
		timeProt.correction.sumTime.second=0;
		timeProt.correction.sumTime.halfmillis=0;
		timeProt.correction.currentTimeOffsetSync.second=0;// to not take the first value
}

extern Channel* pc;

void report(Clock offset){
	uint8_t i;
	
	uint8_t buffer[100];
	uint8_t send[CLP_UTILITY_MAX_PACKET_SIZE];
	buffer[0] = 'V';
	#ifdef MASTERMODE
		buffer[1] = 1;
	#else
		buffer[1] = 2;
	#endif
	//data
	long int time= offset.second*32000+offset.halfmillis;
	buffer[2]=(uint8_t)(time&0x00FF);
	buffer[3]=(uint8_t)((time>>8)&0x00FF);
	buffer[4]=(uint8_t)((time>>16)&0x00FF);
	buffer[5]=(uint8_t)((time>>24)&0x00FF);
	
	size_t length = CLP_GeneratePacket(send, buffer, 6);
	ChannelRadio* radio = ChannelRadio::GetChannel();
