void RecordingSelector::updateRecordingList(void)
{
    if (!m_recordingList || m_recordingList->empty())
        return;

    m_recordingButtonList->Reset();

    if (m_categorySelector)
    {
        ProgramInfo *p;
        vector<ProgramInfo *>::iterator i = m_recordingList->begin();
        for ( ; i != m_recordingList->end(); ++i)
        {
            p = *i;

            if (p->GetTitle() == m_categorySelector->GetValue() ||
                m_categorySelector->GetValue() == tr("All Recordings"))
            {
                MythUIButtonListItem* item = new MythUIButtonListItem(
                    m_recordingButtonList,
                    p->GetTitle() + " ~ " +
                    p->GetScheduledStartTime().toLocalTime()
                    .toString("dd MMM yy (hh:mm)"));
                item->setCheckable(true);
                if (m_selectedList.indexOf((ProgramInfo *) p) != -1)
                {
                    item->setChecked(MythUIButtonListItem::FullChecked);
                }
                else
                {
                    item->setChecked(MythUIButtonListItem::NotChecked);
                }

                QString title = p->GetTitle();
                QString subtitle = p->GetSubtitle();

                QDateTime recstartts = p->GetScheduledStartTime();
                QDateTime recendts   = p->GetScheduledEndTime();

                QString timedate = QString("%1 - %2")
                    .arg(MythDate::toString(recstartts,MythDate::kDateTimeFull))
                    .arg(MythDate::toString(recendts, MythDate::kTime));

                uint season = p->GetSeason();
                uint episode = p->GetEpisode();
                QString seasone, seasonx;

                if (season && episode)
                {
                    seasone = QString("s%1e%2")
                        .arg(format_season_and_episode(season, 2))
                        .arg(format_season_and_episode(episode, 2));
                    seasonx = QString("%1x%2")
                        .arg(format_season_and_episode(season, 1))
                        .arg(format_season_and_episode(episode, 2));
                }

                item->SetText(title, "title");
                item->SetText(subtitle, "subtitle");
                if (subtitle.isEmpty())
                    item->SetText(title, "titlesubtitle");
                else
                    item->SetText(title + " - \"" + subtitle + '"',
                                  "titlesubtitle");

                item->SetText(timedate, "timedate");
                item->SetText(p->GetDescription(), "description");
                item->SetText(formatSize(p->GetFilesize() / 1024),
                              "filesize_str");

                item->SetText(QString::number(season), "season");
                item->SetText(QString::number(episode), "episode");
                item->SetText(seasonx, "00x00");
                item->SetText(seasone, "s00e00");

                item->DisplayState(p->HasCutlist() ? "yes" : "no", "cutlist");

                item->SetData(qVariantFromValue(p));
            }
            qApp->processEvents();
        }
    }

    m_recordingButtonList->SetItemCurrent(m_recordingButtonList->GetItemFirst());
    titleChanged(m_recordingButtonList->GetItemCurrent());
}