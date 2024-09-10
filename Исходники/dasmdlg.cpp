void        DasmDlg::on_execaction_clicked()
{
    QTextCodec *codec = QTextCodec::codecForLocale();

    QString elffile     = m_ui.ElfName->text().trimmed() ;
    QString param       = m_ui.ActParam->text().trimmed ();
    enum EExcDasmMode actmod = EExcDasmAll;

    switch(m_ui.ActMode->currentIndex() ){
        case 0: actmod  = EExcDasmAll; break;
        case 1: actmod  = param.isEmpty() ? EExcDasmFuncList : EExcDasmFuncMatchList;
                break;
        case 2: actmod  = EExcDasmFuncMatch; break;
        case 3: actmod  = EExcDasmFunc;    break;
        case 4: actmod  = EExcDasmAddr;    break;
        default:    break;
    }

    if( elffile.isEmpty() ){
        QMessageBox::warning( 0 /* Core::ICore::instance()->mainWindow()  */,
                codec->toUnicode("无法执行操作"),
                codec->toUnicode("未指定elf文件名"));
        return ;
    }

    if( param.isEmpty() 
            && (actmod == EExcDasmFuncMatch 
                || actmod == EExcDasmFunc 
                || actmod == EExcDasmAddr ) ){
        QMessageBox::warning( 0 /* Core::ICore::instance()->mainWindow()  */,
                codec->toUnicode("无法执行操作"),
                actmod == EExcDasmAddr ? 
                codec->toUnicode("操作需要传入一个数字类型的参数")
                :codec->toUnicode("操作需要传入字符串参数"));
        return ;
    }

    QString tmp ;
    tmp = QDesktopServices::storageLocation(QDesktopServices::TempLocation)+ "/exc_dasm.txt";

    if( actmod  == EExcDasmAll ){
        QString name = QFileDialog::getSaveFileName(this,
                codec->toUnicode("全部反汇编需要的时间较长，你想把反汇编结果另存到文件吗?"), m_curpath, tr("txt Files (*.txt)"));
        if(!name.isEmpty()) {
            tmp = name;
        }
    }

    FILE    *fp = fopen(tmp.toLatin1().data(),"w+");
    if( !fp ){
        QMessageBox::warning  ( 0 /* Core::ICore::instance()->mainWindow()  */,
                codec->toUnicode("无法执行操作"),
                codec->toUnicode("创建输出文件失败"));
        return ;
    }

    int ret     = Exc_Dasm(fp,elffile.toLatin1().data(),
            actmod,param.toLatin1().data());

    QFile scriptFile;
    fseek(fp,0,SEEK_SET);
    scriptFile.open(fp,QIODevice::ReadOnly);   

    m_ui.textEdit->setPlainText(scriptFile.readAll());
    scriptFile.close();

    if( ret != 0 ){
        QString  err;
        err.sprintf("analyse error code:%d",ret);
        QMessageBox::warning( 0 /* Core::ICore::instance()->mainWindow()  */,
                exc_tr("dasm fail"),
                err);
    }
}