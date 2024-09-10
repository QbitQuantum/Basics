void GenGraphForm::doDisplay()
{
    if (exportedFile==QString("")) return;

    std::cout << "OPEN " << (const char*)exportedFile << std::endl;

#ifdef WIN32
    ShellExecuteA(NULL, "open", exportedFile, NULL, NULL, SW_SHOWNORMAL);
#else
    QStringList argv;
    argv << "display" << exportedFile;
#ifdef SOFA_QT4
    QString program = argv.front();
    argv.pop_front();
    //QProcess::startDetached(program, argv); //QString("start \"\"\"")+exportedFile+QString("\"\"\""));
    QProcess::startDetached(program, argv); //QString("start \"\"\"")+exportedFile+QString("\"\"\""));
#else
    QProcess* p = new QProcess(argv, this);
    p->setCommunication(0);
    connect(p,SIGNAL(processExited()),p,SLOT(deleteLater()));
    p->start();
#endif
#endif
}