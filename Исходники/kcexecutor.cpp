QString KCExecutor::getNewConsole()
{
    /*
     * For more information about xTerm, please visit:
     * http://publib.boulder.ibm.com/infocenter/pseries/v5r3/index.jsp?topic=/com.ibm.aix.cmds/doc/aixcmds6/xterm.htm
     *
     * Use a temp file to receive tty destination.
     *
     */
    QTemporaryFile ttyReceiver;
    if(ttyReceiver.open())
    {
        QStringList args;
        //Reset console.
        QSharedPointer<QProcess> console;
        console.reset(new QProcess);
        //Get default terminal.
        Terminal terminal=KCRunner::getDefaultTerminal();
        args<<"-hold"<<"-e"<<"tty>" + ttyReceiver.fileName() +"; while :;do sleep 3600;done";
        console->start(QLatin1String(terminal.terminal_name), args);
        QTextStream _textIn(&ttyReceiver);
        QString tty;
        tty.clear();
        while(tty.length()==0)
        {
            tty=QString(_textIn.readAll());
        }
        tty.remove("\n");
        ttyReceiver.close();
        ttyReceiver.remove();
        //Save console.
        KCExecutor::getInstance()->consoles[tty]=QSharedPointer<QProcess>(console);
        return QString(tty);
    }
    return QString("");
}