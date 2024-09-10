void LanguagePage::retranslateUi()
{
    //% "Change Language"
    setTitle(qtTrId("xx_language_title"));
    if (!isContentCreated())
        return;

    disconnect(comboBoxLanguage, SIGNAL(currentIndexChanged(int)),
               this, SLOT(changeLanguage(int)));
    disconnect(comboBoxLcTime, SIGNAL(currentIndexChanged(int)),
               this, SLOT(changeLcTime(int)));
    disconnect(comboBoxLcTimeFormat24h, SIGNAL(currentIndexChanged(int)),
               this, SLOT(changeLcTimeFormat24h(int)));
    disconnect(comboBoxLcCollate, SIGNAL(currentIndexChanged(int)),
               this, SLOT(changeLcCollate(int)));
    disconnect(comboBoxLcNumeric, SIGNAL(currentIndexChanged(int)),
               this, SLOT(changeLcNumeric(int)));
    disconnect(comboBoxLcMonetary, SIGNAL(currentIndexChanged(int)),
               this, SLOT(changeLcMonetary(int)));

    QStringList localeNames;
#ifdef HAVE_ICU
    int numberOfAvailableLocales = uloc_countAvailable();
    for (int i = 0; i < numberOfAvailableLocales; ++i)
        localeNames << QString::fromUtf8(uloc_getAvailable(i));
    localeNames << "no";
    localeNames << "no_NO";
    localeNames << "es_419";
    localeNames << "de@collation=phonebook";
    localeNames << "de_DE@collation=phonebook";
    localeNames << "zh_Hans_CN@collation=pinyin";
    localeNames << "zh_Hans_CN@collation=stroke";
    QStringList localeNamesWithoutScript;
    QRegExp regexp("^([a-z]{2,3}_)([A-Z][a-z]{3,3}_)(.*)$");
    foreach (const QString &localeName, localeNames) {
        if (regexp.indexIn(localeName) == 0) {
            localeNamesWithoutScript <<
                regexp.capturedTexts().at(1) + regexp.capturedTexts().at(3);
        }
    }
    foreach (const QString &localeName, localeNamesWithoutScript)
        localeNames << localeName;
#else
    for (unsigned language = QLocale::C;
         language <= QLocale::LastLanguage;
         language++) {
        foreach (const QLocale::Country &country,
                 QLocale::countriesForLanguage (QLocale::Language(language))) {
            localeNames << QLocale(QLocale::Language(language), country).name();
        }
    }