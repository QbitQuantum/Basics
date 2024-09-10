template <typename ElemType> nano_time_t
RotPerformanceTest<ElemType>::clblasPerfSingle(void)
{
    nano_time_t time;
    cl_event event;
    cl_int status;
    cl_command_queue queue = base_->commandQueues()[0];

    //DataType type;
    //type = ( typeid(ElemType) == typeid(float))? TYPE_FLOAT: TYPE_DOUBLE;

    status = clEnqueueWriteBuffer(queue, mobjX_, CL_TRUE, 0, (lengthx + params_.offa) * sizeof(ElemType), X_, 0, NULL, &event);
    if (status != CL_SUCCESS)
    {
        cerr << "Vector X buffer object enqueuing error, status = " << status << endl;
        return NANOTIME_ERR;
    }

    status = clEnqueueWriteBuffer(queue, mobjY_, CL_TRUE, 0, (lengthy + params_.offb) * sizeof(ElemType), Y_, 0, NULL, &event);
    if (status != CL_SUCCESS)
    {
        cerr << "Vector Y buffer object enqueuing error, status = " << status << endl;
        return NANOTIME_ERR;
    }

    status = clWaitForEvents(1, &event);
    if (status != CL_SUCCESS)
    {
        cout << "Wait on event failed, status = " << status << endl;
        return NANOTIME_ERR;
    }

    event = NULL;
    time = getCurrentTime();

#define TIMING
#ifdef TIMING
    clFinish( queue);
    int iter = 50;
    for ( int i=1; i <= iter; i++)
    {
#endif
        status = (cl_int)clMath::clblas::rot(params_.N, mobjX_, params_.offa, params_.incx, mobjY_, params_.offb, params_.incy,
                                             alpha, beta, 1, &queue, 0, NULL, &event);
        if (status != CL_SUCCESS)
        {
            cerr << "The CLBLAS ROT function failed, status = " << status << endl;
            return NANOTIME_ERR;
        }
#ifdef TIMING
    } // iter loop
    clFinish( queue);
    time = getCurrentTime() - time;
    time /= iter;
#else

    status = flushAll(1, &queue);
    if (status != CL_SUCCESS)
    {
        cerr << "clFlush() failed, status = " << status << endl;
        return NANOTIME_ERR;
    }

    time = getCurrentTime();
    status = waitForSuccessfulFinish(1, &queue, &event);
    if (status == CL_SUCCESS)
    {
        time = getCurrentTime() - time;
    }
    else
    {
        cerr << "Waiting for completion of commands to the queue failed, "
                "status = " << status << endl;
        time = NANOTIME_ERR;
    }
#endif
    return time;
}