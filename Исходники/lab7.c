void getTime(struct tm *current_time)
{
	time_t sec = 0;
	time(&sec);
	*current_time = *(localtime(&sec)); 
}