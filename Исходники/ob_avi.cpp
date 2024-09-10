void AVIOBJ::CloseAVI(void)												// Properly Closes The Avi File
{

    DeleteObject(hBitmap);										// Delete The Device Dependant Bitmap Object
    if (hdd) DrawDibClose(hdd);											// Closes The DrawDib Device Context
    if (pgf)
    {
        AVIStreamGetFrameClose(pgf);								// Deallocates The GetFrame Resources
        AVIStreamRelease(pavi);										// Release The Stream
        AVIFileExit();												// Release The File
    }

}