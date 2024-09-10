void drawCmdWindow()
{
    if (Touched_Global) {
        WriteConsoleOutput( hOutput[Double_Buffer_Switch], (CHAR_INFO *)screen_buffer, dwBufferSize,
                            dwBufferCoord, &rcRegion );
        SetConsoleActiveScreenBuffer(hOutput[Double_Buffer_Switch]);
        SetConsoleCursorPosition( hOutput[Double_Buffer_Switch], dwBufferSize );
        Double_Buffer_Switch = !Double_Buffer_Switch;
    }
}