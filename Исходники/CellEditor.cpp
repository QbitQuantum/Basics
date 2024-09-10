void CellEditor::triggerFunctionAutoComplete()
{
    // tokenize the expression (don't worry, this is very fast)
    int curPos = textCursor().position();
    QString subtext = toPlainText().left(curPos);

    Calligra::Sheets::Formula f;
    Calligra::Sheets::Tokens tokens = f.scan(subtext);
    if (!tokens.valid()) return;
    if (tokens.count() < 1) return;

    Calligra::Sheets::Token lastToken = tokens[ tokens.count()-1 ];

    // last token must be an identifier
    if (!lastToken.isIdentifier()) return;
    QString id = lastToken.text();
    if (id.length() < 1) return;

    // find matches in function names
    QStringList fnames = Calligra::Sheets::FunctionRepository::self()->functionNames();
    QStringList choices;
    for (int i = 0; i < fnames.count(); i++)
        if (fnames[i].startsWith(id, Qt::CaseInsensitive))
            choices.append(fnames[i]);
    choices.sort();

    // no match, don't bother with completion
    if (!choices.count()) return;

    // single perfect match, no need to give choices
    if (choices.count() == 1)
        if (choices[0].toLower() == id.toLower())
            return;

    // present the user with completion choices
    d->functionCompletion->showCompletion(choices);
}