unsigned __stdcall input_thread_proc(void* args)
{

	//	WaitForSingleObject(ppi_ptr->parallel_stop_event_, ppi_ptr->waiting_time_);
	PARALLEL_PORT_IMPL_PTR ppi_ptr = (PARALLEL_PORT_IMPL_PTR)args;
	DWORD result = 0x0;
	PARALLEL_OUTPUT_QUEUE_ITEM item;
	LARGE_INTEGER  litmp; 
	LONGLONG       QPart1,QPart2;;
	double         minute, freq, tim; 
	int i = 0;

	while(ppi_ptr->is_running_){

		QueryPerformanceFrequency(&litmp); 
		freq = (double)litmp.QuadPart; 
		QueryPerformanceCounter(&litmp); 
		QPart1 = litmp.QuadPart; 

		do{
			result = WaitForSingleObject(ppi_ptr->parallel_stop_event_, 0);
			if(result == WAIT_OBJECT_0)	goto END;

			QueryPerformanceCounter(&litmp); 
			QPart2 = litmp.QuadPart;
			minute = (double)(QPart2-QPart1); 
			tim = minute / freq; 
		}while(tim<0.01);

		for(i = 0; i < 4; ++i){
			if(parallel_output_queue_pop(&item)){
				if(output_data_into_parallel_port(item.buf_, sizeof(item.buf_)) != -1){
					_InterlockedIncrement(&__simple_proc_env.application_environment_->pci_output_num_);
				}
				else{
					OUTPUT_DEBUG_STRING("Write a pallerl error!");
				}
			}
		}

	}
END:

	_endthreadex(0);
	return 0;
}