//	////////////////////////////////////////////////////////////////////////////
char *TimeTM::AscTimeSane(char *buffer) const
{
	//	Necessary because asctime() places a line-feed at the string end.
	char tmp_buffer[Length_TimeTM_AscTime + 1];

	AscTime(tmp_buffer);

	tmp_buffer[Length_TimeTM_AscTimeSane] = '\0';

	return(strcpy(buffer, tmp_buffer));
}