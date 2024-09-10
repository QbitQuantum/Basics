void QHexEditPrivate::keyPressEvent(QKeyEvent *event)
{
    int charX = (_cursorX - _xPosHex) / _charWidth;
    int posX = (charX / 3) * 2 + (charX % 3);
    int posBa = (_cursorY / _charHeight) * BYTES_PER_LINE + posX / 2;


/*****************************************************************************/
/* Cursor movements */
/*****************************************************************************/

    if (event->matches(QKeySequence::MoveToNextChar))
    {
        setCursorPos(_cursorPosition + 1);
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToPreviousChar))
    {
        setCursorPos(_cursorPosition - 1);
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToEndOfLine))
    {
        setCursorPos(_cursorPosition | (2 * BYTES_PER_LINE -1));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToStartOfLine))
    {
        setCursorPos(_cursorPosition - (_cursorPosition % (2 * BYTES_PER_LINE)));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToPreviousLine))
    {
        setCursorPos(_cursorPosition - (2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToNextLine))
    {
        setCursorPos(_cursorPosition + (2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }

    if (event->matches(QKeySequence::MoveToNextPage))
    {
        setCursorPos(_cursorPosition + (((_scrollArea->viewport()->height() / _charHeight) - 1) * 2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToPreviousPage))
    {
        setCursorPos(_cursorPosition - (((_scrollArea->viewport()->height() / _charHeight) - 1) * 2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToEndOfDocument))
    {
        setCursorPos(_xData.size() * 2);
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToStartOfDocument))
    {
        setCursorPos(0);
        resetSelection(_cursorPosition);
    }

/*****************************************************************************/
/* Select commands */
/*****************************************************************************/
    if (event->matches(QKeySequence::SelectAll))
    {
        resetSelection(0);
        setSelection(2*_xData.size() + 1);
    }
    if (event->matches(QKeySequence::SelectNextChar))
    {
        int pos = _cursorPosition + 1;
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectPreviousChar))
    {
        int pos = _cursorPosition - 1;
        setSelection(pos);
        setCursorPos(pos);
    }
    if (event->matches(QKeySequence::SelectEndOfLine))
    {
        int pos = _cursorPosition - (_cursorPosition % (2 * BYTES_PER_LINE)) + (2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectStartOfLine))
    {
        int pos = _cursorPosition - (_cursorPosition % (2 * BYTES_PER_LINE));
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectPreviousLine))
    {
        int pos = _cursorPosition - (2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectNextLine))
    {
        int pos = _cursorPosition + (2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }

    if (event->matches(QKeySequence::SelectNextPage))
    {
        int pos = _cursorPosition + (((_scrollArea->viewport()->height() / _charHeight) - 1) * 2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectPreviousPage))
    {
        int pos = _cursorPosition - (((_scrollArea->viewport()->height() / _charHeight) - 1) * 2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectEndOfDocument))
    {
        int pos = _xData.size() * 2;
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectStartOfDocument))
    {
        int pos = 0;
        setCursorPos(pos);
        setSelection(pos);
    }

/*****************************************************************************/
/* Edit Commands */
/*****************************************************************************/
if (!_readOnly)
{
    /* Hex input */
        int key = int(event->text()[0].toAscii());
        if ((key>='0' && key<='9') || (key>='a' && key <= 'f'))
        {
            if (getSelectionBegin() != getSelectionEnd())
            {
                posBa = getSelectionBegin();
                remove(posBa, getSelectionEnd() - posBa);
                setCursorPos(2*posBa);
                resetSelection(2*posBa);
            }

            // If insert mode, then insert a byte
            if (_overwriteMode == false)
                if ((charX % 3) == 0)
                {
                    insert(posBa, char(0));
                }

            // Change content
            if (_xData.size() > 0)
            {
                QByteArray hexValue = _xData.data().mid(posBa, 1).toHex();
                if ((charX % 3) == 0)
                    hexValue[0] = key;
                else
                    hexValue[1] = key;

                replace(posBa, QByteArray().fromHex(hexValue)[0]);

                setCursorPos(_cursorPosition + 1);
                resetSelection(_cursorPosition);
            }
        }

        /* Cut & Paste */
        if (event->matches(QKeySequence::Cut))
        {
            QString result = QString();
            for (int idx = getSelectionBegin(); idx < getSelectionEnd(); idx++)
            {
                result += _xData.data().mid(idx, 1).toHex() + " ";
                if ((idx % 16) == 15)
                    result.append("\n");
            }
            remove(getSelectionBegin(), getSelectionEnd() - getSelectionBegin());
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(result);
            setCursorPos(getSelectionBegin());
            resetSelection(getSelectionBegin());
        }

        if (event->matches(QKeySequence::Paste))
        {
            QClipboard *clipboard = QApplication::clipboard();
            QByteArray ba = QByteArray().fromHex(clipboard->text().toLatin1());
            insert(_cursorPosition / 2, ba);
            setCursorPos(_cursorPosition + 2 * ba.length());
            resetSelection(getSelectionBegin());
        }


        /* Delete char */
        if (event->matches(QKeySequence::Delete))
        {
            if (getSelectionBegin() != getSelectionEnd())
            {
                posBa = getSelectionBegin();
                remove(posBa, getSelectionEnd() - posBa);
                setCursorPos(2*posBa);
                resetSelection(2*posBa);
            }
            else
            {
                if (_overwriteMode)
                    replace(posBa, char(0));
                else
                    remove(posBa, 1);
            }
        }

        /* Backspace */
        if ((event->key() == Qt::Key_Backspace) && (event->modifiers() == Qt::NoModifier))
            {
                if (getSelectionBegin() != getSelectionEnd())
                {
                    posBa = getSelectionBegin();
                    remove(posBa, getSelectionEnd() - posBa);
                    setCursorPos(2*posBa);
                    resetSelection(2*posBa);
                }
                else
                {
                    if (posBa > 0)
                    {
                        if (_overwriteMode)
                            replace(posBa - 1, char(0));
                        else
                            remove(posBa - 1, 1);
                        setCursorPos(_cursorPosition - 2);
                    }
                }
            }

        /* undo */
        if (event->matches(QKeySequence::Undo))
        {
            undo();
        }

        /* redo */
        if (event->matches(QKeySequence::Redo))
        {
            redo();
        }

    }

    if (event->matches(QKeySequence::Copy))
    {
        QString result = QString();
        for (int idx = getSelectionBegin(); idx < getSelectionEnd(); idx++)
        {
            result += _xData.data().mid(idx, 1).toHex() + " ";
            if ((idx % 16) == 15)
                result.append('\n');
        }
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(result);
    }

    // Switch between insert/overwrite mode
    if ((event->key() == Qt::Key_Insert) && (event->modifiers() == Qt::NoModifier))
    {
        _overwriteMode = !_overwriteMode;
        setCursorPos(_cursorPosition);
        overwriteModeChanged(_overwriteMode);
    }

    _scrollArea->ensureVisible(_cursorX, _cursorY + _charHeight/2, 3, _charHeight/2 + 2);
    adjust();
}