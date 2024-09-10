static void vboxClipboardChanged (VBOXCLIPBOARDCONTEXT *pCtx)
{
    LogFlow(("vboxClipboardChanged\n"));

    if (pCtx->pClient == NULL)
    {
        return;
    }

    /* Query list of available formats and report to host. */
    if (OpenClipboard (pCtx->hwnd))
    {
        uint32_t u32Formats = 0;

        UINT format = 0;

        while ((format = EnumClipboardFormats (format)) != 0)
        {
            LogFlow(("vboxClipboardChanged format %#x\n", format));
            switch (format)
            {
                case CF_UNICODETEXT:
                case CF_TEXT:
                    u32Formats |= VBOX_SHARED_CLIPBOARD_FMT_UNICODETEXT;
                    break;

                case CF_DIB:
                case CF_BITMAP:
                    u32Formats |= VBOX_SHARED_CLIPBOARD_FMT_BITMAP;
                    break;

                default:
                    if (format >= 0xC000)
                    {
                        TCHAR szFormatName[256];

                        int cActual = GetClipboardFormatName(format, szFormatName, sizeof(szFormatName)/sizeof (TCHAR));

                        if (cActual)
                        {
                            if (strcmp (szFormatName, "HTML Format") == 0)
                            {
                                u32Formats |= VBOX_SHARED_CLIPBOARD_FMT_HTML;
                            }
                        }
                    }
                    break;
            }
        }

        CloseClipboard ();

        LogFlow(("vboxClipboardChanged u32Formats %02X\n", u32Formats));

        vboxSvcClipboardReportMsg (pCtx->pClient, VBOX_SHARED_CLIPBOARD_HOST_MSG_FORMATS, u32Formats);
    }
}