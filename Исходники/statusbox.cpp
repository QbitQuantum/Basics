/** \fn StatusBox::doAutoExpireList()
 *  \brief Show list of recordings which may AutoExpire
 */
void StatusBox::doAutoExpireList(bool updateExpList)
{
    if (m_iconState)
        m_iconState->DisplayState("autoexpire");
    m_logList->Reset();

    QString helpmsg(tr("The AutoExpire List shows all recordings "
                       "which may be expired and the order of "
                       "their expiration. Recordings at the top "
                       "of the list will be expired first."));
    if (m_helpText)
        m_helpText->SetText(helpmsg);
    if (m_justHelpText)
        m_justHelpText->SetText(helpmsg);

    ProgramInfo*          pginfo;
    QString               contentLine;
    QString               detailInfo;
    QString               staticInfo;
    long long             totalSize(0);
    long long             liveTVSize(0);
    int                   liveTVCount(0);
    long long             deletedGroupSize(0);
    int                   deletedGroupCount(0);

    vector<ProgramInfo *>::iterator it;

    if (updateExpList)
    {
        for (it = m_expList.begin(); it != m_expList.end(); ++it)
            delete *it;
        m_expList.clear();

        RemoteGetAllExpiringRecordings(m_expList);
    }

    for (it = m_expList.begin(); it != m_expList.end(); ++it)
    {
        pginfo = *it;

        totalSize += pginfo->GetFilesize();
        if (pginfo->GetRecordingGroup() == "LiveTV")
        {
            liveTVSize += pginfo->GetFilesize();
            liveTVCount++;
        }
        else if (pginfo->GetRecordingGroup() == "Deleted")
        {
            deletedGroupSize += pginfo->GetFilesize();
            deletedGroupCount++;
        }
    }

    staticInfo = tr("%n recording(s) consuming %1 (is) allowed to expire\n", "",
                     m_expList.size()).arg(sm_str(totalSize / 1024));

    if (liveTVCount)
        staticInfo += tr("%n (is) LiveTV and consume(s) %1\n", "", liveTVCount)
                            .arg(sm_str(liveTVSize / 1024));

    if (deletedGroupCount)
        staticInfo += tr("%n (is) Deleted and consume(s) %1\n", "",
                        deletedGroupCount)
                        .arg(sm_str(deletedGroupSize / 1024));

    for (it = m_expList.begin(); it != m_expList.end(); ++it)
    {
        pginfo = *it;
        QDateTime starttime = pginfo->GetRecordingStartTime();
        QDateTime endtime = pginfo->GetRecordingEndTime();
        contentLine =
            MythDateTimeToString(starttime, kDateFull | kSimplify) + " - ";

        contentLine +=
            "(" + ProgramInfo::i18n(pginfo->GetRecordingGroup()) + ") ";

        contentLine += pginfo->GetTitle() +
            " (" + sm_str(pginfo->GetFilesize() / 1024) + ")";

        detailInfo =
            MythDateTimeToString(starttime, kDateTimeFull | kSimplify) + " - " +
            MythDateTimeToString(endtime, kDateTimeFull | kSimplify);

        detailInfo += " (" + sm_str(pginfo->GetFilesize() / 1024) + ")";

        detailInfo += " (" + ProgramInfo::i18n(pginfo->GetRecordingGroup()) + ")";

        detailInfo += "\n" + pginfo->toString(ProgramInfo::kTitleSubtitle, " - ");

        AddLogLine(contentLine, staticInfo, detailInfo,
                   staticInfo + detailInfo);
    }
}