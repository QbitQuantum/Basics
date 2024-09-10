void KNNntpClient::doCheckNewGroups()
{
    KNGroupListData *target = static_cast<KNGroupListData *>(job->data());

    sendSignal(TSdownloadNewGroups);
    errorPrefix = i18n("New groups could not be retrieved.\nThe following error occurred:\n");

    progressValue = 100;
    predictedLines = 30;     // rule of thumb ;-)

    QCString cmd;
    cmd.sprintf("NEWGROUPS %.2d%.2d%.2d 000000", target->fetchSince.year() % 100, target->fetchSince.month(), target->fetchSince.day());
    if(!sendCommandWCheck(cmd, 231))      // 231 list of new newsgroups follows
        return;

    char *s, *line;
    QString name;
    KNGroup::Status status;
    QSortedList<KNGroupInfo> tmpList;
    tmpList.setAutoDelete(true);

    while(getNextLine())
    {
        line = getCurrentLine();
        if(line[0] == '.')
        {
            if(line[1] == '.')
                line++;        // collapse double period into one
            else if(line[1] == 0)
                break;   // message complete
        }
        s = strchr(line, ' ');
        if(!s)
        {
#ifndef NDEBUG
            qDebug("knode: retrieved broken group-line - ignoring");
#endif
        }
        else
        {
            s[0] = 0;    // cut string
            name = QString::fromUtf8(line);

            while(s[1] != 0) s++;  // the last character determines the moderation status
            switch(s[0])
            {
                case 'n' :
                    status = KNGroup::readOnly;
                    break;
                case 'y' :
                    status = KNGroup::postingAllowed;
                    break;
                case 'm' :
                    status = KNGroup::moderated;
                    break;
                default  :
                    status = KNGroup::unknown;
            }

            tmpList.append(new KNGroupInfo(name, QString::null, true, false, status));
        }
        doneLines++;
    }

    if(!job->success() || job->canceled())
        return;     // stopped...

    if(target->getDescriptions)
    {
        errorPrefix = i18n("The group descriptions could not be retrieved.\nThe following error occurred:\n");
        progressValue = 100;
        doneLines = 0;
        predictedLines = tmpList.count() * 3;

        sendSignal(TSdownloadDesc);
        sendSignal(TSprogressUpdate);

        cmd = "LIST NEWSGROUPS ";
        QStrList desList;
        char *s;
        int rep;

        for(KNGroupInfo *group = tmpList.first(); group; group = tmpList.next())
        {
            if(!sendCommand(cmd + group->name.utf8(), rep))
                return;
            if(rep != 215)         // 215 informations follows
                break;
            desList.clear();
            if(!getMsg(desList))
                return;

            if(desList.count() > 0)         // group has a description
            {
                s = desList.first();
                while(*s != - '\0' && *s != '\t' && *s != ' ') s++;
                if(*s == '\0')
                {
#ifndef NDEBUG
                    qDebug("knode: retrieved broken group-description - ignoring");
#endif
                }
                else
                {
                    while(*s == ' ' || *s == '\t') s++;     // go on to the description
                    if(target->codecForDescriptions)           // some countries use local 8 bit characters in the tag line
                        group->description = target->codecForDescriptions->toUnicode(s);
                    else
                        group->description = QString::fromLocal8Bit(s);
                }
            }
        }
    }

    sendSignal(TSloadGrouplist);

    if(!target->readIn())
    {
        job->setErrorString(i18n("Unable to read the group list file"));
        return;
    }
    target->merge(&tmpList);
    sendSignal(TSwriteGrouplist);
    if(!target->writeOut())
    {
        job->setErrorString(i18n("Unable to write the group list file"));
        return;
    }
}