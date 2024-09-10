void NetworkAccessManager::HandleDownload(QObject *object){
#ifdef WEBENGINEVIEW
    static QSet<QObject*> set;
    if(set.contains(object)) return;
    set << object;
    connect(object, &QObject::destroyed, [object](){ set.remove(object);});

    Application::AskDownloadPolicyIfNeed();

    DownloadItem *item = new DownloadItem(object);
    QWebEngineDownloadItem *orig_item = qobject_cast<QWebEngineDownloadItem*>(object);

    QString dir = Application::GetDownloadDirectory();
    QString filename;
    QString mime;
    QUrl url;
    if(orig_item){
        if(WebEngineView *w = qobject_cast<WebEngineView*>(Application::CurrentWidget())){
            if(TreeBank *tb = w->GetTreeBank()) tb->GoBackOrCloseForDownload(w);
        }
        filename = orig_item->path();
        mime = orig_item->mimeType();
        url = orig_item->url();
    } else {
        if(QuickWebEngineView *w = qobject_cast<QuickWebEngineView*>(Application::CurrentWidget())){
            if(TreeBank *tb = w->GetTreeBank()) tb->GoBackOrCloseForDownload(w);
        }
        filename = object->property("path").toString();
        mime = object->property("mimeType").toString();
        url = object->property("url").toUrl();
    }

    filename = filename.isEmpty() ? dir
        : dir + filename.split(QStringLiteral("/")).last();

    if(filename.isEmpty() ||
       Application::GetDownloadPolicy() == Application::Undefined_ ||
       Application::GetDownloadPolicy() == Application::AskForEachDownload){

        QString filter;

        QMimeDatabase db;
        QMimeType mimeType = db.mimeTypeForName(mime);
        if(!mimeType.isValid() || mimeType.isDefault()) mimeType = db.mimeTypeForFile(filename);
        if(!mimeType.isValid() || mimeType.isDefault()) mimeType = db.mimeTypeForUrl(url);

        if(mimeType.isValid() && !mimeType.isDefault()) filter = mimeType.filterString();

        filename = ModalDialog::GetSaveFileName_(QString(), filename, filter);
    }

    if(filename.isEmpty()){
        QMetaObject::invokeMethod(object, "cancel");
        item->deleteLater();
        return;
    }

    item->SetPath(filename);
    if(orig_item){
        orig_item->setPath(filename);
    } else {
        object->setProperty("path", filename);
    }
    QMetaObject::invokeMethod(object, "accept");
    MainWindow *win = Application::GetCurrentWindow();
    if(win && win->GetTreeBank()->GetNotifier())
        win->GetTreeBank()->GetNotifier()->RegisterDownload(item);

    QStringList path = filename.split(QStringLiteral("/"));
    path.removeLast();
    Application::SetDownloadDirectory(path.join(QStringLiteral("/")) + QStringLiteral("/"));
#else
    Q_UNUSED(object);
#endif
}