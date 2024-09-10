void FinderSyncHost::doShareLink(const QString &path) {
    QString repo_id;
    Account account;
    QString path_in_repo;
    if (!lookUpFileInformation(path, &repo_id, &account, &path_in_repo)) {
        qWarning("[FinderSync] invalid path %s", path.toUtf8().data());
        return;
    }

    get_shared_link_req_.reset(new GetSharedLinkRequest(
        account, repo_id, QString("/").append(path_in_repo),
        QFileInfo(path).isFile()));

    connect(get_shared_link_req_.get(), SIGNAL(success(const QString &)), this,
            SLOT(onShareLinkGenerated(const QString &)));

    get_shared_link_req_->send();
}