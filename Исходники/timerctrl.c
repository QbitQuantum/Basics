void DelayMsec(unsigned short msec){
	int tick_count= getTickCount();
	while((getTickCount()-tick_count)<msec);
}