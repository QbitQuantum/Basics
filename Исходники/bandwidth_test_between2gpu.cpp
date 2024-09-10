// use_cuda_time = 1: use cudaEventElapsedTime()
// or use getSystemTime()
void test_2gpu(float *d_send_data, float *d_recv_data, int size, int id0, int id1, bool use_cuda_time)
{
	if(use_cuda_time) {
		cudaEvent_t start_event, stop_event;
		float time_memcpy;

		// version I
		//cudaEventCreate(&start_event);
		//cudaEventCreate(&stop_event);
		//cudaEventRecord(start_event, 0);

		// version II
		int eventflags = cudaEventBlockingSync;
		cudaEventCreateWithFlags(&start_event, eventflags);
		cudaEventCreateWithFlags(&stop_event, eventflags);
		cudaEventRecord(start_event, 0);

		for(int i=0; i<CNT; i++) {
			cudaMemcpy(d_recv_data, d_send_data, size*sizeof(float), cudaMemcpyDeviceToDevice);	
		}
		std::cout << "hello, use_cuda_time" << std::endl;

		cudaEventRecord(stop_event, 0);
		cudaEventSynchronize(stop_event);
		cudaEventElapsedTime(&time_memcpy, start_event, stop_event);  // ms
		std::cout << "Time is " << time_memcpy/1000. << "s" << std::endl;
		std::cout << "GPU" << id0 << " ---> GPU" << id1 << " :" << 
			WIDTH*HEIGHT*sizeof(float)*CNT*1000./(1024*1024*time_memcpy) << "MB/s" << std::endl;
		cudaEventDestroy(start_event);
		cudaEventDestroy(stop_event);
	} else {
		//cudaEvent_t start_event;
		//cudaEventCreate(&start_event);

		long long start = getSystemTime();
		for(int i=0; i<CNT; i++) {
			cudaMemcpy(d_recv_data, d_send_data, size*sizeof(float), cudaMemcpyDeviceToDevice);	
			//cudaMemcpyPeer(d_recv_data, id1, d_send_data, id0, size*sizeof(float));	
		}

		//cudaEventRecord(start_event, 0);
		//cudaEventSynchronize(start_event);

		long long end = getSystemTime();
		std::cout << "Time is " << (end-start)/1000. << "s" << std::endl;
		std::cout << "GPU" << id0 << " ---> GPU" << id1 << " :" << 
			WIDTH*HEIGHT*sizeof(float)*CNT*1000./(1024*1024*(end - start+1)) << "MB/s" << std::endl;
	}			//WIDTH*HEIGHT*4.*CNT/(1000*(end - start)) << "Mb/s" << std::endl;
}