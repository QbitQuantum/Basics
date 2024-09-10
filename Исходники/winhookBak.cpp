void getSelectedText(){
    //unHook();
    backupClipboard();

    //模拟发送ctrl+c复制选择的text进粘贴板
    qDebug()<<"准备selected to clipboard";
    //qApp->clipboard()->clear();

    if(clearClipboard()){
        POINT pt;
        GetCursorPos(&pt);//获得当前鼠标位置
        HWND hwnd=WindowFromPoint(pt);//获得鼠标所在的窗口句柄
        QChar buffer[128];
        GetClassName(hwnd,(WCHAR*) buffer, 128);
        QString winclassname=QString::fromRawData(buffer,128);
        qDebug()<<"当前窗口"<<hwnd<<winclassname;
        if(winclassname.contains("Internet Explorer")){//ie以及ie内核的浏览器比如360安全浏览器，不支持发送ctrl+c（划译时不行，但是双击是可以）
            qDebug("ie内核");
            PostMessage(hwnd,WM_COMMAND,0x0001000f,0);//使用spy截获的消息
//        }else if(winclassname.contains("TXGuiFoundation")){
//            qDebug()<<"QQ聊天窗口";
//            SendMessage(hwnd,WM_CHAR,49,49);

        }else{
            //    keybd_event(VK_CONTROL, 0, 0, 0); // 按下 Ctrl
            //    keybd_event('C', 0, 0, 0); // 按下 C
            //    keybd_event('C', 0, KEYEVENTF_KEYUP, 0); // 放开 C
            //    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 放开 Ctrl
           // int bScan=::MapVirtualKey('C',0);
           // qDebug()<<0x1D<<0x2e<<::MapVirtualKey(VK_CONTROL,0)<<::MapVirtualKey('C',0);
            //SendMessage(hwnd,WM_CAPTURECHANGED,0x0,0x0);
            keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_EXTENDEDKEY, 1); // 按下 Ctrl
            keybd_event('C', 0x2E, 0,1); // 按下 C
            //Sleep(10);
            //PostMessage(hwnd,WM_PAINT,0x0,0x0);//使用spy截获的消息

            keybd_event('C', 0x2E, KEYEVENTF_KEYUP, 1); // 放开 C
            keybd_event(VK_CONTROL,0x1D, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 1); // 放开 Ctrl
        }


        int iTimeOut=0;
        while (!qApp->clipboard()->mimeData()->hasText()){//判断剪贴簿内容是否为文字格式
            Sleep(10);
            qApp->processEvents();
            qDebug()<<"wait clip ok"<<iTimeOut<<qApp->clipboard()->text();
            iTimeOut ++;
            if (iTimeOut > 2){
                break;
            }

        }
        //qDebug()<<"wait clip ok"<<iTimeOut;
        if(qApp->clipboard()->mimeData()->hasText()){

            //qDebug()<<"粘贴板内容"<<qApp->clipboard()->text();
            DICT::querySelectedText(qApp->clipboard()->text());
        }
    }
    restoreClipboard();

   // setHook();
}