void ckLowLevelAPI::getWindowsFontDirectory(char* buf, u32 buf_size)
{
    GetWindowsDirectory(buf, buf_size);
    strcat_s(buf, buf_size, "\\Fonts\\");
}