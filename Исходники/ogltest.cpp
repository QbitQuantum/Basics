int OGLTest::Run()
{
    bool fFirst = true;
    MSG msg;
    do
    {
        BOOL fGotMessage;
        if (miRenderStep)
        {
            fGotMessage = GetMessageA(&msg, 0, 0, 0);
        }
        else
        {
            fGotMessage = PeekMessageA(&msg, 0, 0, 0, PM_REMOVE);
        }

        if (fGotMessage)
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        float dt = 0.0f; /* Time in seconds since last render step. @todo Measure. */

        BOOL fDoRender = FALSE;
        if (miRenderStep)
        {
            if (msg.message == WM_CHAR)
            {
                if (msg.wParam == ' ')
                {
                    fDoRender = TRUE;
                    dt = fFirst ? 0.0f : 0.1f; /* 0.1 second increment per step. */
                }
            }
        }
        else
        {
             fDoRender = TRUE;
        }

        if (fDoRender)
        {
            if (mpRender)
            {
                setCurrentGLCtx(mhGLRC);

                mpRender->TimeAdvance(dt);
                mpRender->DoRender();

                setCurrentGLCtx(NULL);

                fFirst = false;
            }
        }
    } while (msg.message != WM_QUIT);

    return msg.wParam;
}