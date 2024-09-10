unsigned long NodeTime::getElapsedSince(unsigned long last_time){
	unsigned long etime = getSystemTime()-last_time;
	if(etime>0){
		return etime;
	}
	else{
		return 4294967295 - last_time + getSystemTime();
	}
}