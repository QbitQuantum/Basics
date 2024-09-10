LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static struct
    {
        int nota;
        int lugar;
        //int largo;
    }notas[NOTA_MAX];

    static int largo=100;
    static int pos=0;

    switch (message)                  /* handle the messages */
    {
        case WM_KEYDOWN:
            if(pos<NOTA_MAX-1)
            switch(wParam)
            {
                case 96:
                    Beep(SIg, largo);
                    notas[pos].nota=SIg;
                    notas[pos].lugar=72;
                    pos++;
                    break;
                case 97:
                    Beep(DO, largo);
                    notas[pos].nota=DO;
                    notas[pos].lugar=66;
                    pos++;
                    break;
                case 98:
                    Beep(RE, largo);
                    notas[pos].nota=RE;
                    notas[pos].lugar=60;
                    pos++;
                    break;
                case 99:
                    Beep(MI, largo);
                    notas[pos].nota=MI;
                    notas[pos].lugar=54;
                    pos++;
                    break;
                case 100:
                    Beep(FA, largo);
                    notas[pos].nota=FA;
                    notas[pos].lugar=48;
                    pos++;
                    break;
                case 101:
                    Beep(SOL, largo);
                    notas[pos].nota=SOL;
                    notas[pos].lugar=42;
                    pos++;
                    break;
                case 102:
                    Beep(LA, largo);
                    notas[pos].nota=LA;
                    notas[pos].lugar=36;
                    pos++;
                    break;
                case 103:
                    Beep(SI, largo);
                    notas[pos].nota=SI;
                    notas[pos].lugar=30;
                    pos++;
                    break;
                case 104:
                    Beep(DOa, largo);
                    notas[pos].nota=DOa;
                    notas[pos].lugar=24;
                    pos++;
                    break;
                case 105:
                    Beep(REa, largo);
                    notas[pos].nota=REa;
                    notas[pos].lugar=18;
                    pos++;
                    break;
            }

            //MessageBox(0,0,0,0);
            //UpdateWindow(hwnd);
            break;
        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hDC;
            hDC = BeginPaint(hwnd, &ps);


            for(int i=0;i<pos;i++)
                Ellipse(hDC, 25+i*15, notas[i].lugar, 37+i*15, notas[i].lugar+12);

            hacerlinea(hDC, 0, 12, 625, 12);
            hacerlinea(hDC, 0, 24, 625, 24);
            hacerlinea(hDC, 0, 36, 625, 36);
            hacerlinea(hDC, 0, 48, 625, 48);
            hacerlinea(hDC, 0, 60, 625, 60);
            hacerlinea(hDC, 10, 10, 10, 62);

            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}