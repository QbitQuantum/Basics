QString TextFormatter::getNewsWidgetFormat(QDomNodeList items)
{
    QString newsLayOut_text;
    newsLayOut_text.append("<font size=5>");

    for(int i = 0; i < items.length(); i++)
    {
        QDomNode item = items.at(i);
        if (m_sMode.compare("rss") == 0)
        {
            newsLayOut_text += getFormattedChannel(item);
        }
        else if (m_sMode.compare("files") == 0)
        {
            newsLayOut_text += getFormattedVacancy(item);
        }

    }

    newsLayOut_text.append("</font>");
    return newsLayOut_text;
}