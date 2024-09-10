//Basic Init, create the font, backbuffer, etc
WINDOW *curses_init(void)
{
   // _windows = new WINDOW[20];         //initialize all of our variables
    lastchar=-1;
    inputdelay=-1;

    std::string typeface = "Terminus";
    char * typeface_c = 0;
    std::ifstream fin;
    fin.open("data\\FONTDATA");
    if (!fin.is_open()){
        fontwidth = 8;
        fontheight = 16;
        std::ofstream fout;//create data/FONDATA file
        fout.open("data\\FONTDATA");
        if(fout.is_open()) {
            fout << typeface << "\n";
            fout << fontwidth << "\n";
            fout << fontheight;
            fout.close();
        }
    } else {
        getline(fin, typeface);
        fin >> fontwidth;
        fin >> fontheight;
        if ((fontwidth <= 4) || (fontheight <=4)){
            MessageBox(WindowHandle, "Invalid font size specified!", NULL, 0);
            fontheight = 16;
            fontwidth  = 8;
        }
    }
    typeface_c = new char [typeface.size()+1];
    strcpy (typeface_c, typeface.c_str());

    halfwidth=fontwidth / 2;
    halfheight=fontheight / 2;
    WindowWidth= (55 + (OPTIONS["VIEWPORT_X"] * 2 + 1)) * fontwidth;
    WindowHeight = (OPTIONS["VIEWPORT_Y"] * 2 + 1) *fontheight;

    WinCreate();    //Create the actual window, register it, etc
    timeBeginPeriod(1); // Set Sleep resolution to 1ms
    CheckMessages();    //Let the message queue handle setting up the window

    WindowDC   = GetDC(WindowHandle);
    backbuffer = CreateCompatibleDC(WindowDC);

    BITMAPINFO bmi = BITMAPINFO();
    bmi.bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth        = WindowWidth;
    bmi.bmiHeader.biHeight       = -WindowHeight;
    bmi.bmiHeader.biPlanes       = 1;
    bmi.bmiHeader.biBitCount     = 8;
    bmi.bmiHeader.biCompression  = BI_RGB; // Raw RGB
    bmi.bmiHeader.biSizeImage    = WindowWidth * WindowHeight * 1;
    bmi.bmiHeader.biClrUsed      = 16; // Colors in the palette
    bmi.bmiHeader.biClrImportant = 16; // Colors in the palette
    backbit = CreateDIBSection(0, &bmi, DIB_RGB_COLORS, (void**)&dcbits, NULL, 0);
    DeleteObject(SelectObject(backbuffer, backbit));//load the buffer into DC

    // Load private fonts
    if (SetCurrentDirectory("data\\font")){
        WIN32_FIND_DATA findData;
        for (HANDLE findFont = FindFirstFile(".\\*", &findData); findFont != INVALID_HANDLE_VALUE; )
        {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){ // Skip folders
                AddFontResourceExA(findData.cFileName, FR_PRIVATE,NULL);
            }
            if (!FindNextFile(findFont, &findData)){
                FindClose(findFont);
                break;
            }
        }
        SetCurrentDirectory("..\\..");
    }

    // Use desired font, if possible
    font = CreateFont(fontheight, fontwidth, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                      ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
                      PROOF_QUALITY, FF_MODERN, typeface_c);

    SetBkMode(backbuffer, TRANSPARENT);//Transparent font backgrounds
    SelectObject(backbuffer, font);//Load our font into the DC
//    WindowCount=0;

    delete typeface_c;
    mainwin = newwin((OPTIONS["VIEWPORT_Y"] * 2 + 1),(55 + (OPTIONS["VIEWPORT_Y"] * 2 + 1)),0,0);
    return mainwin;   //create the 'stdscr' window and return its ref
}