int raw_serial::waitfordata(size_t data_count, _u32 timeout, size_t * returned_size)
{
    COMSTAT  stat;
    DWORD error;
    DWORD msk,length;
    if (returned_size==NULL) returned_size=(size_t *)&length;

    
    if ( isOpened()) {
        size_t rxqueue_remaining =  rxqueue_count();
        if (rxqueue_remaining >= data_count) {
            *returned_size = rxqueue_remaining;
            return 0;
        }
    }

    while ( isOpened() )
    {
        msk = 0;
        SetCommMask(_serial_handle, EV_RXCHAR | EV_ERR );
        if(!WaitCommEvent(_serial_handle, &msk, &_wait_o))
        {
            if(GetLastError() == ERROR_IO_PENDING)
            {
                if (WaitForSingleObject(_wait_o.hEvent, timeout) == WAIT_TIMEOUT)
                {
                    *returned_size =0;
                    return ANS_TIMEOUT;
                }

                GetOverlappedResult(_serial_handle, &_wait_o, &length, TRUE);

                ::ResetEvent(_wait_o.hEvent);
            }else
            {
                ClearCommError(_serial_handle, &error, &stat);
                 *returned_size = stat.cbInQue;
                return ANS_DEV_ERR;
            }
        }

        if(msk & EV_ERR){
            // FIXME: may cause problem here
            ClearCommError(_serial_handle, &error, &stat);
        }

        if(msk & EV_RXCHAR){
            ClearCommError(_serial_handle, &error, &stat);
            if(stat.cbInQue >= data_count)
            {
                *returned_size = stat.cbInQue;
                return 0;
            }
        }
    }
    *returned_size=0;
    return ANS_DEV_ERR;
}