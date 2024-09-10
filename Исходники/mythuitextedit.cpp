bool MythUITextEdit::keyPressEvent(QKeyEvent *event)
{
    m_lastKeyPress.restart();

    QStringList actions;
    bool handled = false;

    handled = GetMythMainWindow()->TranslateKeyPress("Global", event, actions,
                                                     false);

    Qt::KeyboardModifiers modifiers = event->modifiers();
    int keynum = event->key();

    if (keynum >= Qt::Key_Shift && keynum <= Qt::Key_CapsLock)
        return false;

    QString character;
    // Compose key handling
    // Enter composition mode
    if ((modifiers & Qt::GroupSwitchModifier) &&
        (keynum >= Qt::Key_Dead_Grave) && (keynum <= Qt::Key_Dead_Horn))
    {
        m_composeKey = keynum;
        handled = true;
    }
    else if (m_composeKey > 0) // 'Compose' the key
    {
        if (gDeadKeyMap.isEmpty())
            LoadDeadKeys(gDeadKeyMap);

        LOG(VB_GUI, LOG_DEBUG, QString("Compose key: %1 Key: %2").arg(QString::number(m_composeKey, 16)).arg(QString::number(keynum, 16)));

        if (gDeadKeyMap.contains(keyCombo(m_composeKey, keynum)))
        {
            int keycode = gDeadKeyMap.value(keyCombo(m_composeKey, keynum));

            //QKeyEvent key(QEvent::KeyPress, keycode, modifiers);
            character = QChar(keycode);

            if (modifiers & Qt::ShiftModifier)
                character = character.toUpper();
            else
                character = character.toLower();
            LOG(VB_GUI, LOG_DEBUG, QString("Found match for dead-key combo - %1").arg(character));
        }
        m_composeKey = 0;
    }

    if (character.isEmpty())
        character = event->text();

    if (!handled && InsertCharacter(character))
        handled = true;

    for (int i = 0; i < actions.size() && !handled; i++)
    {

        QString action = actions[i];
        handled = true;

        if (action == "LEFT")
        {
            MoveCursor(MoveLeft);
        }
        else if (action == "RIGHT")
        {
            MoveCursor(MoveRight);
        }
        else if (action == "UP")
        {
            handled = MoveCursor(MoveUp);
        }
        else if (action == "DOWN")
        {
            handled = MoveCursor(MoveDown);
        }
        else if (action == "PAGEUP")
        {
            handled = MoveCursor(MovePageUp);
        }
        else if (action == "PAGEDOWN")
        {
            handled = MoveCursor(MovePageDown);
        }
        else if (action == "DELETE")
        {
            RemoveCharacter(m_Position + 1);
        }
        else if (action == "BACKSPACE")
        {
            RemoveCharacter(m_Position);
        }
        else if (action == "NEWLINE")
        {
            QString newmessage = m_Message;
            newmessage.insert(m_Position + 1, '\n');
            SetText(newmessage, false);
            MoveCursor(MoveRight);
        }
        else if (action == "SELECT" && keynum != Qt::Key_Space
                 && GetMythDB()->GetNumSetting("UseVirtualKeyboard", 1) == 1)
        {
            MythScreenStack *popupStack = GetMythMainWindow()->GetStack("popup stack");
            MythUIVirtualKeyboard *kb =  new MythUIVirtualKeyboard(popupStack, this);

            if (kb->Create())
            {
                //connect(kb, SIGNAL(keyPress(QString)), SLOT(keyPress(QString)));
                popupStack->AddScreen(kb);
            }
            else
                delete kb;
        }
        else if (action == "CUT")
        {
            CutTextToClipboard();
        }
        else if (action == "COPY")
        {
            CopyTextToClipboard();
        }
        else if (action == "PASTE")
        {
            PasteTextFromClipboard();
        }
        else
            handled = false;
    }

    return handled;
}