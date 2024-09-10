template <typename ElemType> nano_time_t
HpmvPerformanceTest<ElemType>::clblasPerfSingle(void)
{
    nano_time_t time;
    cl_event event;
    cl_int status;
    cl_command_queue queue = base_->commandQueues()[0];
	int lenY = 1 + (params_.N-1) * abs(params_.incy);

    status = clEnqueueWriteBuffer(queue, mobjY_, CL_TRUE, 0,
                                  (lenY + params_.offCY )* sizeof(ElemType), backY_, 0, NULL, &event);
    if (status != CL_SUCCESS) {
        cerr << "Vector Y buffer object enqueuing error, status = " <<
                 status << endl;

        return NANOTIME_ERR;
    }

    status = clWaitForEvents(1, &event);
    if (status != CL_SUCCESS) {
        cout << "Wait on event failed, status = " <<
                status << endl;

        return NANOTIME_ERR;
    }

    event = NULL;

	time = getCurrentTime();
#define TIMING
#ifdef TIMING

	int iter = 20;
	for ( int i = 1; i <= iter; i++)
	{
#endif
		status = (cl_int)clMath::clblas::hpmv(params_.order, params_.uplo, params_.N, alpha, mobjAP_, params_.offA,
						mobjX_, params_.offBX, params_.incx, beta, mobjY_, params_.offCY, params_.incy,
						1, &queue, 0, NULL, &event);

    if (status != CL_SUCCESS) {
        cerr << "The CLBLAS HPMV function failed, status = " <<
                status << endl;

        return NANOTIME_ERR;
    }

#ifdef TIMING
	} // iter loop
	clFinish( queue);
    time = getCurrentTime() - time;
	time /= iter;
#else

	status = flushAll(1, &queue);
    if (status != CL_SUCCESS) {
        cerr << "clFlush() failed, status = " << status << endl;
        return NANOTIME_ERR;
    }

    time = getCurrentTime();
    status = waitForSuccessfulFinish(1, &queue, &event);
    if (status == CL_SUCCESS) {
        time = getCurrentTime() - time;
    }
    else {
        cerr << "Waiting for completion of commands to the queue failed, "
                "status = " << status << endl;
        time = NANOTIME_ERR;
    }

	//printf("Time elapsed : %lu\n", time);
#endif

    return time;
}