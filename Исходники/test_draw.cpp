int main(int argc, char **argv) {
#ifdef DXPORTLIB
    SetUseCharSet(DX_CHARSET_EXT_UTF8);
#endif
    
    SetWindowText(_T("DxPortLib Test App"));
    SetWindowSizeChangeEnableFlag(TRUE);
    
    SetGraphMode(640, 480, 32);
    ChangeWindowMode(TRUE);
    
    if (DxLib_Init() == -1) {
        return -1;
    }
    
    SRand(0);
    InitBounceThings();
    
    int isWindowed = TRUE;
    int wasPressed = 0;
    int timerDelta = 0;
    int timeLast = GetNowCount();
    int screenshotWasPressed = 0;
    int drawScreen = MakeScreen(640, 480, FALSE);
    
    while (ProcessMessage() == 0
#ifndef DX_NON_INPUT
        && CheckHitKey(KEY_INPUT_ESCAPE) == 0
#endif
    ) {
        /* If Alt+Enter is pressed, flip to fullscreen mode. */
        if (CheckHitKey(KEY_INPUT_RETURN)
            && (CheckHitKey(KEY_INPUT_LALT) || CheckHitKey(KEY_INPUT_RALT))
        ) {
            if (wasPressed == 0) {
                isWindowed = 1 - isWindowed;
                ChangeWindowMode(isWindowed);
            }
            wasPressed = 1;
        } else {
            wasPressed = 0;
        }
        
        /* Game logic here */
        MoveBounceThings();
        
        /* Draw logic here */
        SetDrawScreen(drawScreen);
        SetDrawBright(255, 255, 255);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        DrawFillBox(0, 0, 640, 480, 0xFF000000);
        DrawLineBox(10, 10, 630, 470, 0xFFFFFFFF);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawFillBox(20, 20, 620, 460, GetColor(0x90, 0x80, 0x70));
        
        DrawBounceThings();
        
        if (CheckHitKey(KEY_INPUT_S)) {
            if (screenshotWasPressed == 0) {
                SaveDrawScreenToPNG(0, 0, 640, 480, _T("test_draw_screenshot.png"));
                screenshotWasPressed = 1;
            }
        } else {
            screenshotWasPressed = 0;
        }
        
        SetDrawScreen(DX_SCREEN_BACK);
        DrawGraph(0, 0, drawScreen, FALSE);
        
        ScreenFlip();

        /* Time to next frame automatically... */
        int newTime = GetNowCount();
        timerDelta += newTime - timeLast;
        timeLast = newTime;

        int n = timerDelta;
        if (n > 16) {
            n = 16;
        }
        timerDelta -= n;

        WaitTimer(16 - n);
    }
    
    DxLib_End();
    
    return 0;
}