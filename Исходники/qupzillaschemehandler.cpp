void QupZillaSchemeReply::loadPage()
{
    if (m_loaded)
        return;

    QTextStream stream(&m_buffer);
    stream.setCodec("UTF-8");

    if (m_pageName == QLatin1String("about")) {
        stream << aboutPage();
    }
    else if (m_pageName == QLatin1String("reportbug")) {
        stream << reportbugPage();
    }
    else if (m_pageName == QLatin1String("start")) {
        stream << startPage();
    }
    else if (m_pageName == QLatin1String("speeddial")) {
        stream << speeddialPage();
    }
    else if (m_pageName == QLatin1String("config")) {
        stream << configPage();
    }
    else if (m_pageName == QLatin1String("restore")) {
        stream << restorePage();
    }
    else if (m_pageName == QLatin1String("adblock")) {
        stream << adblockPage();
    }

    stream.flush();
    m_buffer.reset();
    m_loaded = true;
}