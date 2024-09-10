bool WorkItem<T>::StartWork()
{
	work_ = CreateThreadpoolWork(callback, this, callback_env_); 
	if(work_ == nullptr)
	{
		LOG_FATAL();
		return false;
	}

	SubmitThreadpoolWork(work_);
	return true;
}