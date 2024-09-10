void __fastcall TMainCaptureForm::FormCreate(TObject *Sender)
{

	CaptureWorkerForm = new TCaptureWorkerForm(this);
	CaptureWorkerForm1 = new TCaptureWorkerForm(this);
	CaptureWorkerForm2 = new TCaptureWorkerForm(this);
	CaptureWorkerForm3 = new TCaptureWorkerForm(this);
     MainCaptureForm->Caption = UnicodeString("CES Video Stream, version ") + getVersion();
	//There has to be some option other than silent failure and dialog box, but I haven't found it yet.
	//	_control87(MCW_EM, MCW_EM);  //Turn off FPU generated floating point exceptions. Threads still fail however.
	_control87( 0x1372, 0x137F ); //turns on dialog exceptions, but not in TThread. Exceptions in TThread cause the thread to die.


	pBmpRec=new Graphics::TBitmap;
	pBmpRec-> LoadFromFile("Rec.bmp");
	pBmpRecGr=new Graphics::TBitmap;
	pBmpRecGr-> LoadFromFile("Rec-gr.bmp");
	pBmpPau=new Graphics::TBitmap;
	pBmpPau->LoadFromFile("Pau.bmp");
	pBmpPauGr=new Graphics::TBitmap;
	pBmpPauGr->LoadFromFile("Pau-gr.bmp");

	//set default output folder to c:\Users\currentUser\Desktop\capture
 //	char pathC[MAX_PATH];
 //	SHGetSpecialFolderPath(NULL, pathC, CSIDL_DESKTOP, 1);
 //	edOutput->Text = UnicodeString(pathC) + "\\capture";

	frameThread = NULL;
	frameThread1 = NULL;
	frameThread2 = NULL;
	frameThread3 = NULL;
	hMutex = CreateMutex(0,false,0);
	hMutex1 = CreateMutex(0,false,0);
	hMutex2 = CreateMutex(0,false,0);
	hMutex3 = CreateMutex(0,false,0);
	BitBtnStop->Enabled = false;
	FrameDivisorEditChange(this);
	SpatialDivisorEditChange(this);



	allegro_init();
	set_gdi_color_format();
	set_color_depth(CDEPTH);

	nFrames=0;
	SetToVideoMode();

	   // let's refresh the controls according to the TVideoGrabber's states
   AssignListToComboBox (cbVideoInputDevice, CaptureWorkerForm->VideoGrabber->VideoDevices, CaptureWorkerForm->VideoGrabber->VideoDevice);
   AssignListToComboBox (cbVideoInputDevice1, CaptureWorkerForm1->VideoGrabber->VideoDevices, CaptureWorkerForm1->VideoGrabber->VideoDevice);
   AssignListToComboBox (cbVideoInputDevice2, CaptureWorkerForm2->VideoGrabber->VideoDevices, CaptureWorkerForm2->VideoGrabber->VideoDevice);
   AssignListToComboBox (cbVideoInputDevice3, CaptureWorkerForm3->VideoGrabber->VideoDevices, CaptureWorkerForm3->VideoGrabber->VideoDevice);

}