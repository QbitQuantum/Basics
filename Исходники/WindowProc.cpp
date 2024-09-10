static long ProcessShellDDE(HWND w, UINT msg, WPARAM wp, LPARAM lp)
{
    char *command;
    ATOM app,top,a;
    WPARAM hi,lo;
    unsigned short ack;
    char buffer[256];

    switch (msg) {
    case WM_DDE_INITIATE:
        /*
         *	Initiate DDE command
         */

        a = (ATOM)LOWORD(lp);
        if (a == NULL) return 0;
        ::GlobalGetAtomName(a,buffer,sizeof(buffer));
        if (::strcmp(_GDDEAppName,buffer)) return 0;

        a = (ATOM)HIWORD(lp);
        if (a != NULL) {
            ::GlobalGetAtomName(a,buffer,sizeof(buffer));
            if (::strcmp(_GDDETopicName,buffer)) return 0;
        }

        /*
         *	Respond with ACK of only conversation I do
         */

        app = ::GlobalAddAtom(_GDDEAppName);
        top = ::GlobalAddAtom(_GDDETopicName);
        ::SendMessage((HWND)wp,WM_DDE_ACK,(WPARAM)w,MAKELPARAM(app,top));
        ::GlobalDeleteAtom(app);
        ::GlobalDeleteAtom(top);

        return 0;

    case WM_DDE_TERMINATE:
        /*
         *	Terminate DDE connection
         */

        ::PostMessage((HWND)wp,WM_DDE_TERMINATE,(WPARAM)w,0);
        return 0;

    case WM_DDE_EXECUTE:
        /*
         *	Extract command string
         */

        command = (char *)GlobalLock((HANDLE)lp);
        ExecuteDDE(command);
        ::GlobalUnlock((HANDLE)lp);

        ack = 1;
        lo = *(WPARAM *)&ack;
        lp = PackDDElParam(WM_DDE_ACK,lo,lp);
        PostMessage((HWND)wp,WM_DDE_ACK,(LPARAM)w,lp);
        return 0;

    case WM_DDE_UNADVISE:
    case WM_DDE_ADVISE:
    case WM_DDE_DATA:
    case WM_DDE_POKE:
    case WM_DDE_REQUEST:
        /*
         *	Don't do 'em, don't ack 'em!
         */

        UnpackDDElParam(msg,lp,&lo,&hi);
        if ((msg == WM_DDE_ADVISE) || (msg == WM_DDE_DATA) ||
                (msg == WM_DDE_POKE)) {
            ::GlobalFree((HANDLE)lo);
        }
        ack = 0;
        lo = *(WPARAM *)(&ack);
        ReuseDDElParam(lp,msg,WM_DDE_ACK,lo,hi);
        PostMessage((HWND)wp,WM_DDE_ACK,(WPARAM)w,lp);
        return 0;

    default:
        return -1;
    }
}