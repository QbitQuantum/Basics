static void createGtkrc( bool exportColors, const QPalette& cg, bool exportGtkTheme, const QString& gtkTheme, int version )
{
    // lukas: why does it create in ~/.kde/share/config ???
    // pfeiffer: so that we don't overwrite the user's gtkrc.
    // it is found via the GTK_RC_FILES environment variable.
    KSaveFile saveFile( KStandardDirs::locateLocal( "config", 2==version?"gtkrc-2.0":"gtkrc" ) );
    if ( !saveFile.open() )
        return;

    QTextStream t ( &saveFile );
    t.setCodec( QTextCodec::codecForLocale () );

    t << i18n(
            "# created by KDE, %1\n"
            "#\n"
            "# If you do not want KDE to override your GTK settings, select\n"
            "# Appearance -> Colors in the System Settings and disable the checkbox\n"
            "# \"Apply colors to non-KDE4 applications\"\n"
            "#\n"
            "#\n", QDateTime::currentDateTime().toString());

    if ( 2==version ) {  // we should maybe check for MacOS settings here
        t << endl;
        t << "gtk-alternative-button-order = 1" << endl;
        t << endl;
    }

    if (exportGtkTheme)
    {
        QString gtkStyle;
        if (gtkTheme.toLower() == "oxygen")
            gtkStyle = QString("oxygen-gtk");
        else
            gtkStyle = gtkTheme;

        bool exist_gtkrc = false;
        QByteArray gtkrc = getenv(gtkEnvVar(version));
        QStringList listGtkrc = QFile::decodeName(gtkrc).split(":");
        if (listGtkrc.contains(saveFile.fileName()))
            listGtkrc.removeAll(saveFile.fileName());
        listGtkrc.append(QDir::homePath() + userGtkrc(version));
        listGtkrc.append(QDir::homePath() + "/.gtkrc-2.0-kde");
        listGtkrc.append(QDir::homePath() + "/.gtkrc-2.0-kde4");
        listGtkrc.removeAll("");
        listGtkrc.removeDuplicates();
        for (int i = 0; i < listGtkrc.size(); ++i)
        {
            if ((exist_gtkrc = QFile::exists(listGtkrc.at(i))))
                break;
        }

        if (!exist_gtkrc)
        {
            QString gtk2ThemeFilename;
            gtk2ThemeFilename = QString("%1/.themes/%2/gtk-2.0/gtkrc").arg(QDir::homePath()).arg(gtkStyle);
            if (!QFile::exists(gtk2ThemeFilename)) {
                QStringList gtk2ThemePath;
                gtk2ThemeFilename.clear();
                QByteArray xdgDataDirs = getenv("XDG_DATA_DIRS");
                gtk2ThemePath.append(QDir::homePath() + "/.local");
                gtk2ThemePath.append(QFile::decodeName(xdgDataDirs).split(":"));
                gtk2ThemePath.removeDuplicates();
                for (int i = 0; i < gtk2ThemePath.size(); ++i)
                {
                    gtk2ThemeFilename = QString("%1/themes/%2/gtk-2.0/gtkrc").arg(gtk2ThemePath.at(i)).arg(gtkStyle);
                    if (QFile::exists(gtk2ThemeFilename))
                        break;
                    else
                        gtk2ThemeFilename.clear();
                }
            }

            if (!gtk2ThemeFilename.isEmpty())
            {
                t << "include \"" << gtk2ThemeFilename << "\"" << endl;
                t << endl;
                t << "gtk-theme-name=\"" << gtkStyle << "\"" << endl;
                t << endl;
                if (gtkStyle == "oxygen-gtk")
                    exportColors = false;
            }
        }

    }

    if (exportColors)
    {
        t << "style \"default\"" << endl;
        t << "{" << endl;
        t << "  bg[NORMAL] = " << color( cg.color( QPalette::Active, QPalette::Background ) ) << endl;
        t << "  bg[SELECTED] = " << color( cg.color(QPalette::Active, QPalette::Highlight) ) << endl;
        t << "  bg[INSENSITIVE] = " << color( cg.color( QPalette::Active, QPalette::Background ) ) << endl;
        t << "  bg[ACTIVE] = " << color( cg.color( QPalette::Active, QPalette::Mid ) ) << endl;
        t << "  bg[PRELIGHT] = " << color( cg.color( QPalette::Active, QPalette::Background ) ) << endl;
        t << endl;
        t << "  base[NORMAL] = " << color( cg.color( QPalette::Active, QPalette::Base ) ) << endl;
        t << "  base[SELECTED] = " << color( cg.color(QPalette::Active, QPalette::Highlight) ) << endl;
        t << "  base[INSENSITIVE] = " << color( cg.color( QPalette::Active, QPalette::Background ) ) << endl;
        t << "  base[ACTIVE] = " << color( cg.color(QPalette::Active, QPalette::Highlight) ) << endl;
        t << "  base[PRELIGHT] = " << color( cg.color(QPalette::Active, QPalette::Highlight) ) << endl;
        t << endl;
        t << "  text[NORMAL] = " << color( cg.color(QPalette::Active, QPalette::Text) ) << endl;
        t << "  text[SELECTED] = " << color( cg.color(QPalette::Active, QPalette::HighlightedText) ) << endl;
        t << "  text[INSENSITIVE] = " << color( cg.color( QPalette::Active, QPalette::Mid ) ) << endl;
        t << "  text[ACTIVE] = " << color( cg.color(QPalette::Active, QPalette::HighlightedText) ) << endl;
        t << "  text[PRELIGHT] = " << color( cg.color(QPalette::Active, QPalette::HighlightedText) ) << endl;
        t << endl;
        t << "  fg[NORMAL] = " << color ( cg.color( QPalette::Active, QPalette::Foreground ) ) << endl;
        t << "  fg[SELECTED] = " << color( cg.color(QPalette::Active, QPalette::HighlightedText) ) << endl;
        t << "  fg[INSENSITIVE] = " << color( cg.color( QPalette::Active, QPalette::Mid ) ) << endl;
        t << "  fg[ACTIVE] = " << color( cg.color( QPalette::Active, QPalette::Foreground ) ) << endl;
        t << "  fg[PRELIGHT] = " << color( cg.color( QPalette::Active, QPalette::Foreground ) ) << endl;
        t << "}" << endl;
        t << endl;
        t << "class \"*\" style \"default\"" << endl;
        t << endl;

        // tooltips don't have the standard background color
        t << "style \"ToolTip\"" << endl;
        t << "{" << endl;
        QPalette group = QToolTip::palette();
        t << "  bg[NORMAL] = " << color( group.color( QPalette::Active, QPalette::Background ) ) << endl;
        t << "  base[NORMAL] = " << color( group.color( QPalette::Active, QPalette::Base ) ) << endl;
        t << "  text[NORMAL] = " << color( group.color( QPalette::Active, QPalette::Text ) ) << endl;
        t << "  fg[NORMAL] = " << color( group.color( QPalette::Active, QPalette::Foreground ) ) << endl;
        t << "}" << endl;
        t << endl;
        t << "widget \"gtk-tooltip\" style \"ToolTip\"" << endl;
        t << "widget \"gtk-tooltips\" style \"ToolTip\"" << endl;
        t << endl;


        // highlight the current (mouse-hovered) menu-item
        // not every button, checkbox, etc.
        t << "style \"MenuItem\"" << endl;
        t << "{" << endl;
        t << "  bg[PRELIGHT] = " << color( cg.color(QPalette::Highlight) ) << endl;
        t << "}" << endl;
        t << endl;
        t << "class \"*MenuItem\" style \"MenuItem\"" << endl;
        t << endl;
    }

}