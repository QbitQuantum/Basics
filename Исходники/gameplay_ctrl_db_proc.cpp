int gameplay_ctrl_db_proc::logic_valid(const record* rec)
{
#ifdef GAME_SERVER
	//日常任务：提交时间与当前时间 不在1天，原有记录作废
	//每周x任务：提交时间与当前时间 不在1天，原有记录作废
	//指定日期任务：在time_valid处，已经被否定
#ifdef YN_LINUX
	Game_Logic::map_mutex m(&ctrl_db_mutex_);
#endif
  struct tm cur_tm_, commit_tm;	


#ifdef YN_LINUX
	time_t curt;
 	curt = time(NULL);
	localtime_r(&curt, &cur_tm_); 
	localtime_r(&rec->commit_time_, &commit_tm );
#endif
#ifdef YN_WINDOWS
	__time32_t curt;
 	curt = (__time32_t)time(NULL);
	 _localtime32_s(&cur_tm_, &curt ); 
	_localtime32_s( &commit_tm , &rec->commit_time_);
#endif

  if (cur_tm_.tm_year == commit_tm.tm_year &&
      cur_tm_.tm_yday == commit_tm.tm_yday)
  {
  	//同一天，有效
  	return 0;
  }	 
	return -1;
#else
    return 0;
#endif
}