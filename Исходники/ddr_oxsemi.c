void dump_timing(const T_DDR_TIMING_PARAMETERS * data)
{
	int i;
	unsigned int *val = (unsigned int *) data;
	
	for(i=0; i < sizeof(Timing_strings)/sizeof(Timing_strings[0]) ; i++, ++val){
		putText(Timing_strings[i], 40);
		putText(": ",20);
		putHex(*val);
		putC('\n');
	}
}