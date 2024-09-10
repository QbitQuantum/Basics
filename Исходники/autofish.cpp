//Returns the window handle of the given process.
HWND AutoFish::getWindow(LPCSTR processName) {
    HWND hwnd = FindWindowA(0, processName);
    if(!hwnd) {
        std::cout << "Error: Cannot find window!" << std::endl;
        updatelabel("Error: Cannot find window.");
    }
    else {
        //Store the pid in our pid variable address
        GetWindowThreadProcessId(hwnd,&pid);
        std::cout << "Success! Window found!" << std::endl;
        updatelabel("Success! Window Found!");
    }
    return hwnd;
}