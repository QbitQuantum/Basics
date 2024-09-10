void FileTransferDlgNotify::createFile(const QString &name, unsigned size, bool bCanResume)
{
    m_name = name;
    m_size = size;
    m_name = m_name.replace('\\', '/');


    FileTransfer *ft = m_dlg->m_msg->m_transfer;
    int n = m_name.lastIndexOf('/');
    if (n >= 0)
    {
        QString path;
        QString p(m_name.left(n));
        m_fn = m_name.right(m_name.length()-n);
        m_fn = m_fn.replace(QRegExp("/"), "");

        while (!p.isEmpty())
        {
            QString pp = getToken(p, '/');
            if (!path.isEmpty())
                path += '/';
            if (pp == "..")
            {
                QString errMsg = i18n("Bad path: %1") .arg(m_name);
                m_dlg->m_msg->setError(errMsg);
                ft->setError();
                return;
            }
            path += pp;
            QDir dd(ft->dir() /* + '/' + path */);
            QDir d(ft->dir());
            if (dd.exists() || d.mkdir(path))
                continue;

            QString errMsg = i18n("Can't create: %1") .arg(path);
            m_dlg->m_msg->setError(errMsg);
            ft->setError();
            return;
        }
    }
    m_dlg->m_msg->addFile(m_name, size);
    if (m_name.isEmpty() || m_name[(int)(m_name.length() - 1)] == '/')
    {
        ft->startReceive(0);
        return;
    }

    QString shortName = m_name;
    //m_name = ft->dir() + m_name; Quickfix, noragen
    if (m_fn.isEmpty())
        m_fn=m_name;

    m_name = ft->dir() + m_fn;

    if (ft->m_file)
        delete ft->m_file;
    m_dlg->process();
    ft->m_file = new QFile(m_name);
    if (!ft->m_file->exists())
    {
        if (ft->m_file->open(QIODevice::WriteOnly))
        {
            ft->startReceive(0);
            return;
        }
    }
    else switch (ft->overwrite())
        {
        case Skip:
            skip();
            return;
        case Replace:
            if (ft->m_file->open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                ft->startReceive(0);
                return;
            }
            break;
        case Resume:
            if (ft->m_file->open(QIODevice::WriteOnly | QIODevice::Append))
            {
                resume();
                return;
            }
            break;
        default:
            if (ft->m_file->open(QIODevice::WriteOnly | QIODevice::Append))
            {
                QStringList buttons;
                QString forAll;
                if (ft->files())
                    forAll = i18n("For all files");
                buttons.append(i18n("&Replace"));
                buttons.append(i18n("&Skip"));
                if (bCanResume && (ft->m_file->size() < size))
                    buttons.append(i18n("Resu&me"));
                m_dlg->m_ask = new BalloonMsg(NULL, quoteString(i18n("File %1 exists") .arg(shortName)),
                                              buttons, m_dlg->lblState, NULL, false, true, 150, forAll);
                QObject::connect(m_dlg->m_ask, SIGNAL(action(int, void*)), m_dlg, SLOT(action(int, void*)));
                raiseWindow(m_dlg);
                m_dlg->m_ask->show();
                return;
            }
        }