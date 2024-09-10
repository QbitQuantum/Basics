static void WindowChar(char Ch)
{
    if (_CheckBreak  && (Ch == 3))
        Terminate();
    if (KeyCount < sizeof(KeyBuffer))
        {
        KeyBuffer[KeyCount] = Ch;
        ++KeyCount;
        }
}