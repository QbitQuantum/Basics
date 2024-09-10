static char *_internal_clippy_paste(int cb)
{
#if defined(MACOSX)
        char *src;
#endif
#if defined(USE_X11)
        Window owner;
        int getme;
#elif defined(WIN32)
        char *src;
        int clen;
#elif defined(__QNXNTO__)
        void *clhandle;
        PhClipHeader *clheader;
        int *cldata;
#endif

        if (has_sys_clip) {
#if defined(USE_X11)
                if (cb == CLIPPY_SELECT) {
                        getme = XA_PRIMARY;
                } else {
                        getme = atom_clip;
                }
                lock_display();
                owner = XGetSelectionOwner(SDL_Display, getme);
                unlock_display();
                if (owner == None || owner == SDL_Window) {
                        /* fall through to default implementation */
                } else {
                        lock_display();
                        XConvertSelection(SDL_Display, getme, XA_STRING, atom_sel, SDL_Window,
                                                        CurrentTime);
                        /* at some point in the near future, we'll get a SelectionNotify
                        see _x11_clip_filter for more details;

                        because of this (otherwise) oddity, we take the selection immediately...
                        */
                        unlock_display();
                        return NULL;
                }
#else
                if (cb == CLIPPY_BUFFER) {
#if defined(WIN32)
                        if (IsClipboardFormatAvailable(CF_TEXT) && OpenClipboard(SDL_Window)) {
                                _hmem  = GetClipboardData(CF_TEXT);
                                if (_hmem) {
                                        if (_current_selection != _current_clipboard) {
                                                free(_current_clipboard);
                                        }
                                        _current_clipboard = NULL;
                                        src = (char*)GlobalLock(_hmem);
                                        if (src) {
                                                clen = GlobalSize(_hmem);
                                                if (clen > 0) {
                                                        _current_clipboard = mem_alloc(clen+1);
                                                        memcpy(_current_clipboard, src, clen);
                                                        _current_clipboard[clen] = '\0';
                                                }
                                                GlobalUnlock(_hmem);
                                        }
                                }
                                CloseClipboard();
                                _hmem = NULL;
                        }
#elif defined(__QNXNTO__)
                        if (_current_selection != _current_clipboard) {
                                free(_current_clipboard);
                        }
                        _current_clipboard = NULL;
#if (NTO_VERSION < 620)
                        clhandle = PhClipboardPasteStart(inputgroup);
                        if (clhandle) {
                                clheader = PhClipboardPasteType(clhandle,
                                                                Ph_CLIPBOARD_TYPE_TEXT);
                                if (clheader) {
                                        cldata = clheader->data;
                                        if (clheader->length > 4 && *cldata == Ph_CL_TEXT) {
                                                src = ((char *)clheader->data)+4;
                                                clen = clheader->length - 4;
                                                _current_clipboard = mem_alloc(clen+1);
                                                memcpy(_current_clipboard, src, clen);
                                                _current_clipboard[clen] = '\0';

                                        }
                                        PhClipboardPasteFinish(clhandle);
                                }
                        }
#else
                        /* argh! qnx */
                        clheader = PhClipboardRead(inputgroup, Ph_CLIPBOARD_TYPE_TEXT);
                        if (clheader) {
                                cldata = clheader->data;
                                if (clheader->length > 4 && *cldata == Ph_CL_TEXT) {
                                        src = ((char *)clheader->data)+4;
                                        clen = clheader->length - 4;
                                        _current_clipboard = mem_alloc(clen+1);
                                        memcpy(_current_clipboard, src, clen);
                                        _current_clipboard[clen] = '\0';
                                }
                        }
#endif /* NTO version selector */
                /* okay, we either own the buffer, or it's a selection for folks without */
#endif /* win32/qnx */
                }
#endif /* x11/others */
                /* fall through; the current window owns it */
        }
        if (cb == CLIPPY_SELECT) return _current_selection;
#ifdef MACOSX
        if (cb == CLIPPY_BUFFER) {
                src = str_dup(macosx_clippy_get());
                if (_current_clipboard != _current_selection) {
                        free(_current_clipboard);
                }
                _current_clipboard = src;
                if (!src) return (char *) ""; /* FIXME: de-const-ing is bad */
                return _current_clipboard;
        }
#else
        if (cb == CLIPPY_BUFFER) return _current_clipboard;
#endif
        return NULL;
}