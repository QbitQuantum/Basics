//Basic Init, create the font, backbuffer, etc
WINDOW *initscr(void)
{
   // _windows = new WINDOW[20];         //initialize all of our variables
    BITMAPINFO bmi;
    lastchar=-1;
    inputdelay=-1;
    std::string typeface;
char * typeface_c;
std::ifstream fin;
fin.open("data\\FONTDATA");
 if (!fin.is_open()){
     MessageBox(WindowHandle, "Failed to open FONTDATA, loading defaults.",
                NULL, NULL);
     fontheight=16;
     fontwidth=8;
 } else {
     getline(fin, typeface);
     typeface_c= new char [typeface.size()+1];
     strcpy (typeface_c, typeface.c_str());
     fin >> fontwidth;
     fin >> fontheight;
     if ((fontwidth <= 4) || (fontheight <=4)){
         MessageBox(WindowHandle, "Invalid font size specified!",
                    NULL, NULL);
        fontheight=16;
        fontwidth=8;
     }
 }
    halfwidth=fontwidth / 2;
    halfheight=fontheight / 2;
    WindowWidth=80*fontwidth;
    WindowHeight=25*fontheight;
    WindowX=(GetSystemMetrics(SM_CXSCREEN) / 2)-WindowWidth/2;    //center this
    WindowY=(GetSystemMetrics(SM_CYSCREEN) / 2)-WindowHeight/2;   //sucker
    WinCreate();    //Create the actual window, register it, etc
    CheckMessages();    //Let the message queue handle setting up the window
    WindowDC = GetDC(WindowHandle);
    backbuffer = CreateCompatibleDC(WindowDC);
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = WindowWidth;
    bmi.bmiHeader.biHeight = -WindowHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount=8;
    bmi.bmiHeader.biCompression = BI_RGB;   //store it in uncompressed bytes
    bmi.bmiHeader.biSizeImage = WindowWidth * WindowHeight * 1;
    bmi.bmiHeader.biClrUsed=16;         //the number of colors in our palette
    bmi.bmiHeader.biClrImportant=16;    //the number of colors in our palette
    backbit = CreateDIBSection(0, &bmi, DIB_RGB_COLORS, (void**)&dcbits, NULL, 0);
    DeleteObject(SelectObject(backbuffer, backbit));//load the buffer into DC

 int nResults = AddFontResourceExA("data\\termfont",FR_PRIVATE,NULL);
   if (nResults>0){
    font = CreateFont(fontheight, fontwidth, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                      ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
                      PROOF_QUALITY, FF_MODERN, typeface_c);   //Create our font

  } else {
      MessageBox(WindowHandle, "Failed to load default font, using FixedSys.",
                NULL, NULL);
       font = CreateFont(fontheight, fontwidth, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                      ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
                      PROOF_QUALITY, FF_MODERN, "FixedSys");   //Create our font
   }
    //FixedSys will be user-changable at some point in time??
    SetBkMode(backbuffer, TRANSPARENT);//Transparent font backgrounds
    SelectObject(backbuffer, font);//Load our font into the DC
//    WindowCount=0;

    delete typeface_c;
    mainwin = newwin(25,80,0,0);
    return mainwin;   //create the 'stdscr' window and return its ref
};