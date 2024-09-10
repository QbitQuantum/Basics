void MasterConfiguration::loadMasterSettings()
{
    QXmlQuery query;
    if(!query.setFocus(QUrl(filename_)))
    {
        put_flog(LOG_FATAL, "failed to load %s", filename_.toLatin1().constData());
        exit(-1);
    }

    loadDockStartDirectory(query);
    loadWebBrowserStartURL(query);
}