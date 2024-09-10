tm *TimeUtil::get_current_tm()
{
	const time_t timeTmp = get_current_time();
	return localtime( &timeTmp );
}