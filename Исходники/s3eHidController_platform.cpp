s3eResult s3eHidControllerInit_platform()
{
    CreateInputWindow();
        
    HRESULT hr = DirectDrawCreateEx( NULL, (LPVOID *)&idd7, IID_IDirectDraw7, NULL );
    if (hr != DD_OK) { IwError(("Couldn't initialize DirectDraw() :( ErrCode=0x%X\n", (uint32)hr)); }

    return S3E_RESULT_SUCCESS;
}