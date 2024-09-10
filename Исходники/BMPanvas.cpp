//******************************************
HRESULT BMPanvas::LoadImage( CString name )
{
    HRESULT ret;
    CImage TI;
    if((ret=TI.Load(name))==S_OK)
    {
        HDC thdc=TI.GetDC();
        hdc=CreateCompatibleDC(thdc);
        TI.ReleaseDC();
        if(hdc!=NULL)
        {
            Attach(TI.Detach());
            FileName=name;
        }
    }
    return ret;
}