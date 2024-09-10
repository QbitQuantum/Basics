void
get_scrap(int type, int *dstlen, char **dst)
{
    scrap_type format;

    *dstlen = 0;
    format = convert_format(type);

#if defined(WZ_WS_X11)
    /* * */
    {
        Window owner;
        Atom selection;
        Atom seln_type;
        int seln_format;
        unsigned long nbytes;
        unsigned long overflow;
        unsigned char * src;

        Lock_Display();
        owner = XGetSelectionOwner(SDL_Display, XA_PRIMARY);
        Unlock_Display();
        if ( (owner == None) || (owner == SDL_Window) )
        {
            owner = DefaultRootWindow(SDL_Display);
            selection = XA_CUT_BUFFER0;
        }
        else
        {
            int selection_response = 0;
            SDL_Event event;

            owner = SDL_Window;
            Lock_Display();
            selection = XInternAtom(SDL_Display, "SDL_SELECTION", False);
            XConvertSelection(SDL_Display, XA_PRIMARY, format,
                              selection, owner, CurrentTime);
            Unlock_Display();
            while ( ! selection_response )
            {
                SDL_WaitEvent(&event);
                if ( event.type == SDL_SYSWMEVENT )
                {
                    XEvent xevent = event.syswm.msg->event.xevent;

                    if ( (xevent.type == SelectionNotify) &&
                            (xevent.xselection.requestor == owner) )
                        selection_response = 1;
                }
            }
        }
        Lock_Display();
        if ( XGetWindowProperty(SDL_Display, owner, selection, 0, INT_MAX/4,
                                False, format, &seln_type, &seln_format,
                                &nbytes, &overflow, &src) == Success )
        {
            if ( seln_type == format )
            {
                *dstlen = convert_scrap(type, NULL, (char*)src, nbytes);
                *dst = (char *)realloc(*dst, *dstlen);
                if ( *dst == NULL )
                    *dstlen = 0;
                else
                    convert_scrap(type, *dst, (char*)src, nbytes);
            }
            XFree(src);
        }
        Unlock_Display();
    }

#elif defined(WZ_WS_WIN)
    /* * */
    if ( IsClipboardFormatAvailable(format) && OpenClipboard(SDL_Window) )
    {
        HANDLE hMem;
        char *src;

        hMem = GetClipboardData(format);
        if ( hMem != NULL )
        {
            src = (char *)GlobalLock(hMem);
            *dstlen = convert_scrap(type, NULL, src, 0);
            *dst = (char *)realloc(*dst, *dstlen);
            if ( *dst == NULL )
                *dstlen = 0;
            else
                convert_scrap(type, *dst, src, 0);
            GlobalUnlock(hMem);
        }
        CloseClipboard();
    }
#elif defined(WZ_WS_QNX)
    /* * */
#if (_NTO_VERSION < 620) /* before 6.2.0 releases */
    {
        void* clhandle;
        PhClipHeader* clheader;
        int* cldata;

        clhandle=PhClipboardPasteStart(InputGroup);
        if (clhandle!=NULL)
        {
            clheader=PhClipboardPasteType(clhandle, Ph_CLIPBOARD_TYPE_TEXT);
            if (clheader!=NULL)
            {
                cldata=clheader->data;
                if ((clheader->length>4) && (*cldata==type))
                {
                    *dstlen = convert_scrap(type, NULL, (char*)clheader->data+4, clheader->length-4);
                    *dst = (char *)realloc(*dst, *dstlen);
                    if (*dst == NULL)
                    {
                        *dstlen = 0;
                    }
                    else
                    {
                        convert_scrap(type, *dst, (char*)clheader->data+4, clheader->length-4);
                    }
                }
            }
            PhClipboardPasteFinish(clhandle);
        }
    }
#else /* 6.2.0 and 6.2.1 and future releases */
    {
        void* clhandle;
        PhClipboardHdr* clheader;
        int* cldata;

        clheader=PhClipboardRead(InputGroup, Ph_CLIPBOARD_TYPE_TEXT);
        if (clheader!=NULL)
        {
            cldata=clheader->data;
            if ((clheader->length>4) && (*cldata==type))
            {
                *dstlen = convert_scrap(type, NULL, (char*)clheader->data+4, clheader->length-4);
                *dst = (char *)realloc(*dst, *dstlen);
                if (*dst == NULL)
                {
                    *dstlen = 0;
                }
                else
                {
                    convert_scrap(type, *dst, (char*)clheader->data+4, clheader->length-4);
                }
            }
        }
    }
#endif
#endif /* scrap type */
}