 void cursor_visible(bool state){
     static auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_CURSOR_INFO     cursorInfo;
     GetConsoleCursorInfo(handle, &cursorInfo);
     cursorInfo.bVisible = state; // set the cursor visibility
     SetConsoleCursorInfo(handle, &cursorInfo);
 }