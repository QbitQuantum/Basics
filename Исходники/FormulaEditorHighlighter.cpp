void FormulaEditorHighlighter::highlightBlock(const QString& text)
{
    // reset syntax highlighting
    setFormat(0, text.length(), QApplication::palette().text().color());

    // save the old ones to identify range changes
    Tokens oldTokens = d->tokens;

    // interpret the text as formula
    // we accept invalid/incomplete formulas
    Formula f;
    d->tokens = f.scan(text);

    QFont editorFont = document()->defaultFont();
    QFont font;

    uint oldRangeCount = d->rangeCount;

    d->rangeCount = 0;
    QList<QColor> colors = d->selection->colors();
    QList<QString> alreadyFoundRanges;

    Sheet *const originSheet = d->selection->originSheet();
    Map *const map = originSheet->map();

    for (int i = 0; i < d->tokens.count(); ++i) {
        Token token = d->tokens[i];
        Token::Type type = token.type();

        switch (type) {
        case Token::Cell:
        case Token::Range: {
            // don't compare, if we have already found a change
            if (!d->rangeChanged && i < oldTokens.count() && token.text() != oldTokens[i].text()) {
                d->rangeChanged = true;
            }

            const Region newRange(token.text(), map, originSheet);
            if (!newRange.isValid()) {
                continue;
            }

            int index = alreadyFoundRanges.indexOf(newRange.name());
            if (index == -1) { /* not found */
                alreadyFoundRanges.append(newRange.name());
                index = alreadyFoundRanges.count() - 1;
            }
            const QColor color(colors[index % colors.size()]);
            setFormat(token.pos() + 1, token.text().length(), color);
            ++d->rangeCount;
        }
        break;
        case Token::Boolean:     // True, False (also i18n-ized)
            /*        font = QFont(editorFont);
                    font.setBold(true);
                    setFormat(token.pos() + 1, token.text().length(), font);*/
            break;
        case Token::Identifier:   // function name or named area*/
            /*        font = QFont(editorFont);
                    font.setBold(true);
                    setFormat(token.pos() + 1, token.text().length(), font);*/
            break;

        case Token::Unknown:
        case Token::Integer:     // 14, 3, 1977
        case Token::Float:       // 3.141592, 1e10, 5.9e-7
        case Token::String:      // "KOffice", "The quick brown fox..."
        case Token::Error:
            break;
        case Token::Operator: {  // +, *, /, -
            switch (token.asOperator()) {
            case Token::LeftPar:
            case Token::RightPar:
                //Check where this brace is in relation to the cursor and highlight it if necessary.
                handleBrace(i);
                break;
            default:
                break;
            }
        }
        break;
        }
    }

    if (oldRangeCount != d->rangeCount)
        d->rangeChanged = true;
}