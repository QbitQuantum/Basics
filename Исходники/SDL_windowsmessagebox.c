static WIN_DialogData *CreateDialogData(int w, int h, const char *caption)
{
    WIN_DialogData *dialog;
    DLGTEMPLATEEX dialogTemplate;
    WORD WordToPass;

    SDL_zero(dialogTemplate);
    dialogTemplate.dlgVer = 1;
    dialogTemplate.signature = 0xffff;
    dialogTemplate.style = (WS_CAPTION | DS_CENTER | DS_SHELLFONT);
    dialogTemplate.x = 0;
    dialogTemplate.y = 0;
    dialogTemplate.cx = w;
    dialogTemplate.cy = h;
    Vec2ToDLU(&dialogTemplate.cx, &dialogTemplate.cy);

    dialog = (WIN_DialogData *)SDL_calloc(1, sizeof(*dialog));
    if (!dialog) {
        return NULL;
    }

    if (!AddDialogData(dialog, &dialogTemplate, sizeof(dialogTemplate))) {
        FreeDialogData(dialog);
        return NULL;
    }

    /* No menu */
    WordToPass = 0;
    if (!AddDialogData(dialog, &WordToPass, 2)) {
        FreeDialogData(dialog);
        return NULL;
    }

    /* No custom class */
    if (!AddDialogData(dialog, &WordToPass, 2)) {
        FreeDialogData(dialog);
        return NULL;
    }

    /* title */
    if (!AddDialogString(dialog, caption)) {
        FreeDialogData(dialog);
        return NULL;
    }

    /* Font stuff */
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE ToPass;

        NONCLIENTMETRICSA NCM;
        NCM.cbSize = sizeof(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        /* Font size - convert to logical font size for dialog parameter. */
        {
            HDC ScreenDC = GetDC(0);
            WordToPass = (WORD)(-72 * NCM.lfMessageFont.lfHeight / GetDeviceCaps(ScreenDC, LOGPIXELSY));
            ReleaseDC(0, ScreenDC);
        }

        if (!AddDialogData(dialog, &WordToPass, 2)) {
            FreeDialogData(dialog);
            return NULL;
        }

        /* Font weight */
        WordToPass = (WORD)NCM.lfMessageFont.lfWeight;
        if (!AddDialogData(dialog, &WordToPass, 2)) {
            FreeDialogData(dialog);
            return NULL;
        }

        /* italic? */
        ToPass = NCM.lfMessageFont.lfItalic;
        if (!AddDialogData(dialog, &ToPass, 1)) {
            FreeDialogData(dialog);
            return NULL;
        }

        /* charset? */
        ToPass = NCM.lfMessageFont.lfCharSet;
        if (!AddDialogData(dialog, &ToPass, 1)) {
            FreeDialogData(dialog);
            return NULL;
        }

        /* font typeface. */
        if (!AddDialogString(dialog, NCM.lfMessageFont.lfFaceName)) {
            FreeDialogData(dialog);
            return NULL;
        }
    }

    return dialog;
}