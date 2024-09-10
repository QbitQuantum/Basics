void StatisticsAPI::getAllProjectLangStats(const QString &projectSlug, const QVariantList &resources, int accountIdx)
{
    if (resources.isEmpty()) {
        emit gotAllProjectLangStatsError(tr("No resources set."));
        return;
    }

    getAllProjectLangStatsNm.setAccountIndex(accountIdx);
    projectLangStats.clear();
    projectLangStatsCounter = resources.length();


    for (int i = 0; i < resources.length(); ++i)
    {
        QUrl url = helper.buildUrl("/project/" + projectSlug + "/resource/" + resources.at(i).toString() + "/stats/", accountIdx);

        connect(&getAllProjectLangStatsNm, SIGNAL(finished(QNetworkReply*)), this, SLOT(getAllProjectLangStatsFinished(QNetworkReply*)), Qt::UniqueConnection);

        getAllProjectLangStatsNm.get(QNetworkRequest(url));
    }
}