bool Window::savefile( char* dlgTitle, char* initDir, char* filterStr, char* resultFile )
{
  OPENFILENAMEA ofn = { 0 };
    
  ofn.Flags = OFN_OVERWRITEPROMPT |  // prompts in case selects file that exists
              OFN_PATHMUSTEXIST;  // path must exist, else dialog box won't return

  ofn.hInstance = hInstance ;
  ofn.hwndOwner = hwnd;

  ofn.lStructSize = sizeof(OPENFILENAMEA);
    
  ofn.lpstrTitle = dlgTitle ;
  ofn.lpstrInitialDir = initDir;
  ofn.lpstrFilter = filterStr; //"md2 files (*.md2)\0*.md2\0All files (*.*)\0*.*\0\0";

  ofn.lpstrFile = resultFile;   // ptr to string that will contain 
                                // FILE USER CHOSE when call to
                                // GetOpenFileNameA( &ofn ) returns.

  ofn.nMaxFile  = MAX_PATH;     // length of the resultFile string

  return (GetSaveFileNameA( &ofn ));   // GetOpenFileName returns false
                                       // when user clicks cancel, or if err
}