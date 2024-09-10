/// \brief For add message info, this function is thread safe
void DebugEngine::addDebugInformation(const DebugLevel_custom &level,const QString& function,const QString& text,QString file,const int& ligne,const QString& location)
{
    if(DebugEngine::debugEngine==NULL)
    {
        qWarning() << "After close: " << function << file << ligne;
        return;
    }
    //Remove the compiler extra patch generated
    file=file.remove(QRegularExpression("\\.\\.?[/\\\\]([^/]+[/\\\\])?"));
    QString addDebugInformation_lignestring=QString::number(ligne);
    QString addDebugInformation_fileString=file;
    if(ligne!=-1)
        addDebugInformation_fileString+=":"+addDebugInformation_lignestring;
    //Load the time from start
    QString addDebugInformation_time = QString::number(startTime.elapsed());
    QString addDebugInformation_htmlFormat;
    bool important=true;
    switch(level)
    {
        case DebugLevel_custom_Information:
            addDebugInformation_htmlFormat="<tr class=\"Information\"><td class=\"time\">"+addDebugInformation_time+"</span></td><td>"+addDebugInformation_fileString+"</td><td class=\"function\">"+function+"()</td><td class=\"location\">"+location+"</td><td>"+htmlEntities(text)+"</td></tr>\n";
        break;
        case DebugLevel_custom_Critical:
            addDebugInformation_htmlFormat="<tr class=\"Critical\"><td class=\"time\">"+addDebugInformation_time+"</span></td><td>"+addDebugInformation_fileString+"</td><td class=\"function\">"+function+"()</td><td class=\"location\">"+location+"</td><td>"+htmlEntities(text)+"</td></tr>\n";
        break;
        case DebugLevel_custom_Warning:
            addDebugInformation_htmlFormat="<tr class=\"Warning\"><td class=\"time\">"+addDebugInformation_time+"</span></td><td>"+addDebugInformation_fileString+"</td><td class=\"function\">"+function+"()</td><td class=\"location\">"+location+"</td><td>"+htmlEntities(text)+"</td></tr>\n";
        break;
        case DebugLevel_custom_Notice:
        {
            addDebugInformation_htmlFormat="<tr class=\"Notice\"><td class=\"time\">"+addDebugInformation_time+"</span></td><td>"+addDebugInformation_fileString+"</td><td class=\"function\">"+function+"()</td><td class=\"location\">"+location+"</td><td>"+htmlEntities(text)+"</td></tr>\n";
            important=false;
        }
        break;
        case DebugLevel_custom_UserNote:
            addDebugInformation_htmlFormat="<tr class=\"Note\"><td class=\"time\">"+addDebugInformation_time+"</span></td><td>"+addDebugInformation_fileString+"</td><td class=\"function\">"+function+"()</td><td class=\"location\">"+location+"</td><td>"+htmlEntities(text)+"</td></tr>\n";
        break;
    }
    //To prevent access of string in multi-thread
    {
        //Show the text in console
        QString addDebugInformation_textFormat;
        addDebugInformation_textFormat = "("+addDebugInformation_time.rightJustified(8,' ')+") ";
        if(file!="" && ligne!=-1)
            addDebugInformation_textFormat += file+":"+addDebugInformation_lignestring+":";
        addDebugInformation_textFormat += function+"(), (location: "+location+"): "+text;
        QMutexLocker lock_mutex(&mutex);
        if(currentBackend==File)
        {
            if(logFile.size()<ULTRACOPIER_DEBUG_MAX_ALL_SIZE*1024*1024 || (important && logFile.size()<ULTRACOPIER_DEBUG_MAX_IMPORTANT_SIZE*1024*1024))
            {
                puts(qPrintable(addDebugInformation_textFormat));
                logFile.write(addDebugInformation_htmlFormat.toUtf8());
            }
        }
        else
        {
            if(debugHtmlContent.size()<ULTRACOPIER_DEBUG_MAX_ALL_SIZE*1024*1024 || (important && debugHtmlContent.size()<ULTRACOPIER_DEBUG_MAX_IMPORTANT_SIZE*1024*1024))
            {
                puts(qPrintable(addDebugInformation_textFormat));
                debugHtmlContent+=addDebugInformation_htmlFormat;
            }
        }
        //Send the new line
        if(addDebugInformationCallNumber<ULTRACOPIER_DEBUG_MAX_GUI_LINE)
        {
            addDebugInformationCallNumber++;
            DebugModel::debugModel->addDebugInformation(startTime.elapsed(),level,function,text,file,ligne,location);
        }
    }
}