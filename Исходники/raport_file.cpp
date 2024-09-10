void GRaportManager::UpdateTime(GClock & clock)
{
	if(!time_period(clock)) return;

	if(flush_period(clock))
	{
		if(raport_file) 
		{
			fflush(raport_file);
#ifdef LINUX
			struct stat buf;
			int ret= stat( file_name, &buf );
#else
			struct __stat64 buf;
			int ret= _stat64( file_name, &buf );
#endif
			if(ret==-1){fclose(raport_file);raport_file=NULL;wait_for_data=true;}
		}
		overflow_lines=0;
	}
	UpdateName(clock);
}