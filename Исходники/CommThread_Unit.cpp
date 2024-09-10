//---------------------------------------------------------------------------
void __fastcall TCommThread::Open()
{
        if(Connected==false)
        {
                //Open device
                DeviceHandle=CreateFile(        DeviceName.c_str(),
                                                GENERIC_READ|GENERIC_WRITE,
                                                FILE_SHARE_DELETE,
                                                NULL,
                                                OPEN_EXISTING,
                                                FILE_ATTRIBUTE_TEMPORARY|FILE_FLAG_DELETE_ON_CLOSE,
                                                NULL
                                        );

                if(DeviceHandle!=INVALID_HANDLE_VALUE)
                {
                        //Make backup and set DCB of open device
                        GetCommState(DeviceHandle,&OriginalDCB);
                        SetCommState(DeviceHandle,&MyDCB);

                        //Make backup and set COMMTIMEOUTS of open device
                        GetCommTimeouts(DeviceHandle,&OriginalTimeouts);
                        SetCommTimeouts(DeviceHandle,&MyTimeouts);

                        SetupComm(DeviceHandle,1024*ReceiveQueue,1024*TransmitQueue);

                        //Resume Thread
                        if(this->Suspended)
                                Resume();
                        Connected=true;
                }//if
        }//if
}