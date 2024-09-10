BOOL MyConnect(HWND hDlg)
{
    WSADATA wsaData;
    SOCKADDR_IN myaddr, serveraddr;
    int nRtn;
    SOCKET s;
    HOSTENT *lpHostent;
    unsigned int addr;
    MYPACKET packet;
    int fromlen;
    time_t server_tm;
    struct tm *lpgtime;
    SYSTEMTIME st;

    // �@ WinSockを初期化
    nRtn = WSAStartup(MAKEWORD(1, 1), &wsaData);
    if (nRtn != 0) {
        MessageBox(hDlg, 
            "Winsock初期化失敗です", 
            szAppName, 
            MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    // �A ソケットをオープン
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == INVALID_SOCKET) {
        MessageBox(hDlg, "socket失敗", 
            szAppName, MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        return FALSE;
    }

    // �B SOCKADDR_IN構造体のメンバをセット
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    // �C ソケットに名前を付ける
    nRtn = bind(s, (SOCKADDR *)&myaddr, sizeof(myaddr));
    if (nRtn != 0) {
        MessageBox(hDlg, "bind Error", 
            szAppName, MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return FALSE;
    }

    // �D ホスト情報を取得
    lpHostent = gethostbyname(szServer);
    if (lpHostent == NULL) {
        addr = inet_addr(szServer);
        lpHostent = gethostbyaddr((char *)&addr, 4, AF_INET);
        if (lpHostent == NULL) {
            MessageBox(hDlg, "ホストを特定できません",
                szAppName, MB_OK | MB_ICONEXCLAMATION);
            closesocket(s);
            WSACleanup();
            return FALSE;
        }
    }

    // �E SOCKADDR_IN構造体のメンバにサーバ情報をセット
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(sport);
    serveraddr.sin_addr.s_addr = 
        *((unsigned long *)lpHostent->h_addr);

    // �F Control_Wordメンバに0x0B000000をセット
    memset(&packet, 0, sizeof(MYPACKET));
    packet.Control_Word = htonl(0x0B000000);

    // �G パケットを送信
    nRtn = sendto(s, (const char *)&packet, sizeof(MYPACKET), 
        0, (SOCKADDR *)&serveraddr,sizeof(serveraddr));
    if (nRtn == SOCKET_ERROR) {
        MessageBox(hDlg, "パケット送信エラーです", szAppName,
            MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return FALSE;
    }

    // �H サーバからの返事を待機
    fromlen = sizeof(SOCKADDR_IN);
    nRtn = recvfrom(s, (char *)&packet, sizeof(MYPACKET), 
        0, (SOCKADDR *)&serveraddr, &fromlen);
    if (nRtn == SOCKET_ERROR) {
        MessageBox(hDlg, "受信エラーです", 
            szAppName, MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return FALSE;
    }

    // サーバから返された時刻を変数に保管
    server_tm =
        ntohl(packet.transmit_timestamp_seconds) - 2208988800;
    // サーバからの時刻をtm構造体に変換
    lpgtime = gmtime(&server_tm);

    // SYSTEMTIME構造体のメンバをセット
    st.wYear = lpgtime->tm_year + 1900;
    st.wMonth = lpgtime->tm_mon + 1;
    st.wDay = lpgtime->tm_mday;
    st.wHour = lpgtime->tm_hour;
    st.wMinute = lpgtime->tm_min;
    st.wSecond = lpgtime->tm_sec;
    st.wMilliseconds = 0;

    // コンピュータの時刻を、サーバから取得した時刻に合わせる
    if (SetSystemTime(&st) != 0) {
        MessageBox(hDlg, "システム時間をサーバ時間に合わせました",
            szAppName, MB_OK);
    }

    closesocket(s);          // ソケットをクローズ
    WSACleanup();            // WinSockのリソースを解放

    return TRUE;
}