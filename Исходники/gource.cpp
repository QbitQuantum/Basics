void createWindowsConsole() {
    if(consoleWindow !=0) return;

    //create a console on Windows so users can see messages

    //find an available name for our window
    int console_suffix = 0;
    char consoleTitle[512];
    sprintf(consoleTitle, "%s", "Gource Console");

    while(FindWindowA(0, consoleTitle)) {
        sprintf(consoleTitle, "Gource Console %d", ++console_suffix);
    }

    AllocConsole();
    SetConsoleTitleA(consoleTitle);

    //redirect streams to console
    freopen("conin$", "r", stdin);
    freopen("conout$","w", stdout);
    freopen("conout$","w", stderr);

    consoleWindow = 0;

    //wait for our console window
    while(consoleWindow==0) {
        consoleWindow = FindWindowA(0, consoleTitle);
        SDL_Delay(100);
    }

    //disable the close button so the user cant crash gource
    HMENU hm = GetSystemMenu(consoleWindow, false);
    DeleteMenu(hm, SC_CLOSE, MF_BYCOMMAND);
}