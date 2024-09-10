BOOL APIENTRY DrvSwapLayerBuffers(HDC hdc, UINT fuPlanes)
{
    CR_DDI_PROLOGUE();
    if (fuPlanes == 1)
    {
        return DrvSwapBuffers(hdc);
    }
    else
    {
        crWarning( "DrvSwapLayerBuffers: unsupported" );
        CRASSERT(false);
        return 0;
    }
}