void QTouchSettingWidget::onChangeLanguage()
{
    if( !isWindow() ) return;

    QLangRes& Res = QLangManager::instance()->getResource();

    setWindowTitle( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("WINDOW_CAPTION")) );
    ui->LBSlow1->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TEXT_SLOW")) );
    ui->LBSlow2->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TEXT_SLOW")) );
    ui->LBFast1->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TEXT_FAST")) );
    ui->LBFast2->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TEXT_FAST")) );
    ui->BtnDefault->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("BTN_CAPTION_DEFAULT")) );
    ui->BtnClose->setText( Res.getResString(QString::fromUtf8("COMMON"), QString::fromUtf8("TEXT_CLOSE")) );

    ui->TitleTimeSetting->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TITLE_TIME_SETTING")) );
    ui->TitleWheelZoomSetting->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TITLE_WHEEL_SENSITIVITY_SETTING")) );

    ui->LBTap->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TEXT_TAP")) );
    ui->LBLongTap->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TEXT_LONG_TAP")) );
    ui->LBWheel->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TEXT_WHEEL")) );
    ui->LBZoom->setText( Res.getResString(QString::fromUtf8("TOUCH SETTING"), QString::fromUtf8("TEXT_ZOOM")) );

    ui->TitleTouchSensitivity->setText( Res.getResString(QString::fromUtf8("CALIBRATION SETTING"), QString::fromUtf8("TITLE_TOUCH_SENSITIVITY")) );
    ui->LBSensitivity->setText( Res.getResString(QString::fromUtf8("CALIBRATION SETTING"), QString::fromUtf8("TEXT_SENSITIVITY")) );

    Qt::AlignmentFlag eFlag = Res.isR2L() ? Qt::AlignLeft : Qt::AlignRight;
    ui->EditTap->setAlignment( eFlag );
    ui->EditLongTap->setAlignment( eFlag );
    ui->EditWheel->setAlignment( eFlag );
    ui->EditZoom->setAlignment( eFlag );
}