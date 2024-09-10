//------------------------------------------------------------------------------
MetaInfo BibleQuoteModule::readInfo(QFile &file)
{
    bool useShortName = false;
    m_moduleName.clear();
    m_moduleShortName.clear();
    int countlines = 0;

    QString encoding = getEncodingFromFile(file.fileName());
    m_codec = QTextCodec::codecForName(encoding.toStdString().c_str());

    QTextDecoder *decoder = m_codec->makeDecoder();
    while(!file.atEnd())
    {
        /*if (countlines > 50) { //wenn eine ini datei ungueltig ist soll damit nicht zuviel zeit verguedet werden
            break;
        }*/
        QByteArray byteline = file.readLine();
        QString line = decoder->toUnicode(byteline);
        if(!line.startsWith("//"))
        {
            countlines++;
        }
        else
        {
            continue;
        }

        if(line.contains("BibleName", Qt::CaseInsensitive) and m_moduleName.isEmpty())
        {
            m_moduleName = formatFromIni(line.
                                         remove(QRegExp("BibleName(\\s*)=(\\s*)",
                                                        Qt::CaseInsensitive)));
            if(m_moduleName.isEmpty())
            {
                useShortName = true;
            }
            if(useShortName && !m_moduleShortName.isEmpty())
            {
                break;
            }
            /// what is ?
            //            else if(!useShortName)
            //            {
            //                break;
            //            }
        }
        if(line.contains("BibleShortName", Qt::CaseInsensitive) and m_moduleShortName.isEmpty())
        {
            m_moduleShortName = formatFromIni(line.
                                              remove(QRegExp("BibleShortName(\\s*)=(\\s*)",
                                                             Qt::CaseInsensitive)));
            if(useShortName)
                break;
        }
    }
    file.close();
    if(useShortName)
    {
        m_moduleName = m_moduleShortName;
    }
    if(m_moduleName.isEmpty())
    {
        myWarning() << "invalid ini File " << file.fileName();
    }

    MetaInfo ret;
    ret.setName(m_moduleName);
    ret.setShortName(m_moduleShortName);

    if (m_typeModule == "Apocrypha")
        ret.type = OBVCore::Type_BibleQuoteApocrypha;

    if (m_typeModule == "Comments")
        ret.type = OBVCore::Type_BibleQuoteComments;

    if (m_typeModule == "Bible")
        ret.type = OBVCore::Type_BibleQuoteModule;

    if (m_typeModule == "Book")
        ret.type = OBVCore::Type_BibleQuoteBook;

    return ret;
    return MetaInfo();
}