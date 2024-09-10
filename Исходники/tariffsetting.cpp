void CTariffSetting::CompareTime( QTimeEdit &edtTime, QTime &time, bool bSequence )
{
    if ( !edtTime.isVisible( ) ) {
        return;
    }

    bool bDisplay = bSequence ? ( time > edtTime.time( ) ) : ( time < edtTime.time( ) );
    QString strStyle = bDisplay ? "background-color: rgb(255, 0, 0);" :
                       "background-color: rgb(255, 255, 255);";

    if ( bDisplay ) {
        edtTime.setFocus( );
        QString strInfo = QString( "%1时间不能%2于%3时间" ).arg( bSequence ? "截止" : "起始",
                                                          bSequence ? "小" : "大",
                                                          bSequence ? "起始" : "截止" );
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 strInfo, QMessageBox::Information );
    }

    QString strWhite = "background-color: rgb(255, 255, 255);";

    ui->tdtSection1->setStyleSheet( strWhite );
    ui->tdtSection2->setStyleSheet( strWhite );

    edtTime.setStyleSheet( strStyle );
}