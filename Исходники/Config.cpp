/*!
  Load, parse, and process a qdoc configuration file. This
  function is only called by the other load() function, but
  this one is recursive, i.e., it calls itself when it sees
  an \c{include} statement in the qdog configuration file.
 */
void Config::load(Location location, const QString& fileName)
{
    QRegExp keySyntax("\\w+(?:\\.\\w+)*");

#define SKIP_CHAR() \
    do { \
        location.advance(c); \
        ++i; \
        c = text.at(i); \
        cc = c.unicode(); \
    } while (0)

#define SKIP_SPACES() \
    while (c.isSpace() && cc != '\n') \
        SKIP_CHAR()

#define PUT_CHAR() \
    word += c; \
    SKIP_CHAR();

    if (location.depth() > 16)
        location.fatal(tr("Too many nested includes"));

    QFile fin(fileName);
    if (!fin.open(QFile::ReadOnly | QFile::Text)) {
        fin.setFileName(fileName + ".qdoc");
        if (!fin.open(QFile::ReadOnly | QFile::Text))
            location.fatal(tr("Cannot open file '%1': %2").arg(fileName).arg(fin.errorString()));
    }

    QTextStream stream(&fin);
    stream.setCodec("UTF-8");
    QString text = stream.readAll();
    text += QLatin1String("\n\n");
    text += QChar('\0');
    fin.close();

    location.push(fileName);
    location.start();

    int i = 0;
    QChar c = text.at(0);
    uint cc = c.unicode();
    while (i < (int) text.length()) {
        if (cc == 0)
            ++i;
        else if (c.isSpace()) {
            SKIP_CHAR();
        }
        else if (cc == '#') {
            do {
                SKIP_CHAR();
            } while (cc != '\n');
        }
        else if (isMetaKeyChar(c)) {
            Location keyLoc = location;
            bool plus = false;
            QString stringValue;
            QStringList stringListValue;
            QString word;
            bool inQuote = false;
            bool prevWordQuoted = true;
            bool metWord = false;

            MetaStack stack;
            do {
                stack.process(c, location);
                SKIP_CHAR();
            } while (isMetaKeyChar(c));

            QStringList keys = stack.getExpanded(location);
            //qDebug() << "KEYS:" << keys;
            SKIP_SPACES();

            if (keys.count() == 1 && keys.first() == "include") {
                QString includeFile;

                if (cc != '(')
                    location.fatal(tr("Bad include syntax"));
                SKIP_CHAR();
                SKIP_SPACES();
                while (!c.isSpace() && cc != '#' && cc != ')') {
                    includeFile += c;
                    SKIP_CHAR();
                }
                SKIP_SPACES();
                if (cc != ')')
                    location.fatal(tr("Bad include syntax"));
                SKIP_CHAR();
                SKIP_SPACES();
                if (cc != '#' && cc != '\n')
                    location.fatal(tr("Trailing garbage"));

                /*
                  Here is the recursive call.
                 */
                load(location,
                      QFileInfo(QFileInfo(fileName).dir(), includeFile)
                      .filePath());
            }
            else {
                /*
                  It wasn't an include statement, so it;s something else.
                 */
                if (cc == '+') {
                    plus = true;
                    SKIP_CHAR();
                }
                if (cc != '=')
                    location.fatal(tr("Expected '=' or '+=' after key"));
                SKIP_CHAR();
                SKIP_SPACES();

                for (;;) {
                    if (cc == '\\') {
                        int metaCharPos;

                        SKIP_CHAR();
                        if (cc == '\n') {
                            SKIP_CHAR();
                        }
                        else if (cc > '0' && cc < '8') {
                            word += QChar(c.digitValue());
                            SKIP_CHAR();
                        }
                        else if ((metaCharPos = QString::fromLatin1("abfnrtv").indexOf(c)) != -1) {
                            word += "\a\b\f\n\r\t\v"[metaCharPos];
                            SKIP_CHAR();
                        }
                        else {
                            PUT_CHAR();
                        }
                    }
                    else if (c.isSpace() || cc == '#') {
                        if (inQuote) {
                            if (cc == '\n')
                                location.fatal(tr("Unterminated string"));
                            PUT_CHAR();
                        }
                        else {
                            if (!word.isEmpty()) {
                                if (metWord)
                                    stringValue += QLatin1Char(' ');
                                stringValue += word;
                                stringListValue << word;
                                metWord = true;
                                word.clear();
                                prevWordQuoted = false;
                            }
                            if (cc == '\n' || cc == '#')
                                break;
                            SKIP_SPACES();
                        }
                    }
                    else if (cc == '"') {
                        if (inQuote) {
                            if (!prevWordQuoted)
                                stringValue += QLatin1Char(' ');
                            stringValue += word;
                            if (!word.isEmpty())
                                stringListValue << word;
                            metWord = true;
                            word.clear();
                            prevWordQuoted = true;
                        }
                        inQuote = !inQuote;
                        SKIP_CHAR();
                    }
                    else if (cc == '$') {
                        QString var;
                        SKIP_CHAR();
                        while (c.isLetterOrNumber() || cc == '_') {
                            var += c;
                            SKIP_CHAR();
                        }
                        if (!var.isEmpty()) {
                            char *val = getenv(var.toLatin1().data());
                            if (val == 0) {
                                location.fatal(tr("Environment variable '%1' undefined").arg(var));
                            }
                            else {
                                word += QString(val);
                            }
                        }
                    }
                    else {
                        if (!inQuote && cc == '=')
                            location.fatal(tr("Unexpected '='"));
                        PUT_CHAR();
                    }
                }

                QStringList::ConstIterator key = keys.begin();
                while (key != keys.end()) {
                    if (!keySyntax.exactMatch(*key))
                        keyLoc.fatal(tr("Invalid key '%1'").arg(*key));

                    if (plus) {
                        if (locMap[*key].isEmpty()) {
                            locMap[*key] = keyLoc;
                        }
                        else {
                            locMap[*key].setEtc(true);
                        }
                        if (stringValueMap[*key].isEmpty()) {
                            stringValueMap[*key] = stringValue;
                        }
                        else {
                            stringValueMap[*key] +=
                                QLatin1Char(' ') + stringValue;
                        }
                        stringListValueMap[*key] += stringListValue;
                    }
                    else {
                        locMap[*key] = keyLoc;
                        stringValueMap[*key] = stringValue;
                        stringListValueMap[*key] = stringListValue;
                    }
                    ++key;
                }
            }
        }
        else {
            location.fatal(tr("Unexpected character '%1' at beginning of line")
                            .arg(c));
        }
    }
}