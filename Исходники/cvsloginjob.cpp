bool CvsLoginJob::execute()
{
    static QByteArray repository;

    int res = m_Proc->exec(m_CvsClient, m_Arguments);
    if( res < 0 )
    {
        qCDebug(log_cervisia) << "Couldn't start 'cvs login' process!";
        return false;
    }

    bool result = false;
    while( true )
    {
        QByteArray line = m_Proc->readLine();
        if( line.isNull() )
        {
            return result;
        }

        // add line to output list
        m_output << line;
        qCDebug(log_cervisia) << "process output = " << line;

        // retrieve repository from 'Logging in to'-line
        if( line.contains(LOGIN_PHRASE) )
        {
            repository = line.remove(0, line.indexOf(":pserver:"));
            continue;
        }

        // process asks for the password
        // search case insensitive as cvs and cvsnt use different capitalization
        if( line.toUpper().contains(PASS_PHRASE) )
        {

            // show password dialog
            QString password;
            KPasswordDialog dlg;
            dlg.setPrompt(i18n("Enter password for repository %1.").arg(QString::fromLocal8Bit(repository)));
            if( dlg.exec() )
            {
                password = dlg.password();
                // send password to process
                m_Proc->waitSlave();
                m_Proc->writeLine(password.toLocal8Bit());

                // wait for the result
                while( !line.contains(FAILURE_PHRASE) )
                {
                    line = m_Proc->readLine();
                    if( line.isNull() )
                        return true;

                    // add line to output list
                    m_output << line;
                    qCDebug(log_cervisia) << "process output = " << line;
                }

                result = false;
            }
            else
            {
                // user pressed cancel so kill the process
                kill(m_Proc->pid(), SIGKILL);
                m_Proc->waitForChild();
                result = false;
            }
        }
    }
    return false;
}