void SoftwareGraphicsDevice::FinishRender(WindowObjects &O, AppInterface &App)
{
    UINT Width = O.GetWindowManager().GetWidth();
    UINT Height = O.GetWindowManager().GetHeight();
    Info.bmiHeader.biWidth = Width;
    Info.bmiHeader.biHeight = Height;

    //load Bmp into our window (represented by hDC)
    SetDIBitsToDevice(hDC, 0, 0, Width, Height, 0, 0, 0, Height, &Bmp[0][0], &Info, DIB_RGB_COLORS);
}