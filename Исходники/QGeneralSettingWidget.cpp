void QGeneralSettingWidget::on_RBMultiTouchWin7_clicked()
{
#if defined(Q_OS_WIN)
    OSVERSIONINFOW Info;
    Info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
    if( GetVersionEx( &Info ) )
    {
        if( Info.dwMajorVersion <= 6 && Info.dwMinorVersion <= 1 )
        {
            bool bMsg = false;
            if( Info.dwMajorVersion == 6 && Info.dwMinorVersion == 1 )
            {
                typedef bool (WINAPI *fnGetProductInfo)(DWORD, DWORD, DWORD, DWORD, PDWORD);
                DWORD dwType = 0;
                fnGetProductInfo GetProductInfo = (fnGetProductInfo)GetProcAddress( GetModuleHandle(L"kernel32.dll"), "GetProductInfo" );
                GetProductInfo( Info.dwMajorVersion, Info.dwMinorVersion, 0, 0, &dwType );
                if( dwType == 0x00000002 || // PRODUCT_HOME_BASIC
                    dwType == 0x00000043 || // PRODUCT_HOME_BASIC_E
                    dwType == 0x00000005 || // PRODUCT_HOME_BASIC_N
                    dwType == 0x0000000B || // PRODUCT_STARTER
                    dwType == 0x00000042 || // PRODUCT_STARTER_E
                    dwType == 0x0000002F )  // RPODUCT_STARTER_N
                {
                    bMsg = true;
                }
            }
            else
            {
                bMsg = true;
            }

            if( bMsg )
            {
                QLangRes& Res = QLangManager::instance()->getResource();
                QString strMessage = Res.getResString( QString::fromUtf8("SETTING"), QString::fromUtf8("TEXT_INPUT_MODE_WARNING_MSG") );
                QString strMsgTitle = Res.getResString( QString::fromUtf8("WARNING SENSOR DIAGNOSIS"), QString::fromUtf8("TITLE_CAPTION") );

                QMessageBox msgBox( this );
                msgBox.setWindowTitle( strMsgTitle );
                msgBox.setText( strMessage );
                msgBox.setStandardButtons( QMessageBox::Yes | QMessageBox::No );
                msgBox.setIcon( QMessageBox::Warning );
                msgBox.setButtonText( QMessageBox::Yes, Res.getResString( QString::fromUtf8("MESSAGEBOX"), QString::fromUtf8("BTN_CAPTION_YES") ) );
                msgBox.setButtonText( QMessageBox::No, Res.getResString( QString::fromUtf8("MESSAGEBOX"), QString::fromUtf8("BTN_CAPTION_NO") ) );
                msgBox.setFont( font() );

                if( msgBox.exec() != QMessageBox::Yes )
                {
                    RBMultiTouchWin7->setChecked( false );
                    RBMouse->setChecked( true );
                    return;
                }
            }
        }