void AVI :: Close(void)												// Properly Closes The Avi File
{
	if(mpf)
	{
		DeleteObject(hBitmap);										// Delete The Device Dependant Bitmap Object
		DrawDibClose(hdd);											// Closes The DrawDib Device Context
		AVIStreamGetFrameClose(pgf);								// Deallocates The GetFrame Resources
		AVIStreamRelease(pavi);										// Release The Stream
		AVIFileExit();												// Release The File
	}

	// clear everything else
	pos=0;
	width=height=0;
	mpf=0;
	pdata=NULL;
	loop=false;
}