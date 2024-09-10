static void
text_new_line(TW *tw)
{
        tw->CursorPos.x = 0;
        tw->CursorPos.y++;
        if (tw->CursorPos.y >= tw->ScreenSize.y) {
            int i =  tw->ScreenSize.x * (tw->ScreenSize.y - 1);
                memmove(tw->ScreenBuffer, tw->ScreenBuffer+tw->ScreenSize.x,
                        i * CHARSIZE);
#ifdef WINDOWS_NO_UNICODE
                memset(tw->ScreenBuffer + i, ' ', tw->ScreenSize.x);
#else
                wmemset(tw->ScreenBuffer + i, ' ', tw->ScreenSize.x);
#endif
                tw->CursorPos.y--;
                ScrollWindow(tw->hwnd,0,-tw->CharSize.y,NULL,NULL);
                UpdateWindow(tw->hwnd);
        }
        if (tw->CursorFlag)
                text_to_cursor(tw);

/*	TextMessage(); */
}