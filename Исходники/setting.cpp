void Setting::showWindow() {
    HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT src = {0, 0, this->getWindowWidth() - 1, this->getWindowHeight() - 1};
    SetConsoleWindowInfo (out_handle, true, &src);
    COORD coord = {this->getWindowWidth(), this->getWindowHeight()};
    SetConsoleScreenBufferSize (out_handle, coord);
    SetConsoleTitle(this->windowTitle.c_str());
    std::string buff;
    buff.append("color");
    buff.append(" ");
    buff.append(this->windowColor);
    system(buff.c_str());
}