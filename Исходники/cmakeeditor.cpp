QString CMakeEditor::contextHelpId() const
{
    int pos = position();

    QChar chr;
    do {
        --pos;
        if (pos < 0)
            break;
        chr = characterAt(pos);
        if (chr == QLatin1Char('('))
            return QString();
    } while (chr.unicode() != QChar::ParagraphSeparator);

    ++pos;
    chr = characterAt(pos);
    while (chr.isSpace()) {
        ++pos;
        chr = characterAt(pos);
    }
    int begin = pos;

    do {
        ++pos;
        chr = characterAt(pos);
    } while (chr.isLetterOrNumber() || chr == QLatin1Char('_'));
    int end = pos;

    while (chr.isSpace()) {
        ++pos;
        chr = characterAt(pos);
    }

    // Not a command
    if (chr != QLatin1Char('('))
        return QString();

    QString command = textAt(begin, end - begin).toLower();
    return QLatin1String("command/") + command;
}