void KeyEvent::fromScriptValue(const QScriptValue& object, KeyEvent& event) {
    
    event.isValid = false; // assume the worst
    event.isMeta = object.property("isMeta").toVariant().toBool();
    event.isControl = object.property("isControl").toVariant().toBool();
    event.isAlt = object.property("isAlt").toVariant().toBool();
    event.isKeypad = object.property("isKeypad").toVariant().toBool();
    event.isAutoRepeat = object.property("isAutoRepeat").toVariant().toBool();
    
    QScriptValue key = object.property("key");
    if (key.isValid()) {
        event.key = key.toVariant().toInt();
        event.text = QString(QChar(event.key));
        event.isValid = true;
    } else {
        QScriptValue text = object.property("text");
        if (text.isValid()) {
            event.text = object.property("text").toVariant().toString();
            
            // if the text is a special command, then map it here...
            // TODO: come up with more elegant solution here, a map? is there a Qt function that gives nice names for keys?
            if (event.text.toUpper() == "F1") {
                event.key = Qt::Key_F1;
            } else if (event.text.toUpper() == "F2") {
                event.key = Qt::Key_F2;
            } else if (event.text.toUpper() == "F3") {
                event.key = Qt::Key_F3;
            } else if (event.text.toUpper() == "F4") {
                event.key = Qt::Key_F4;
            } else if (event.text.toUpper() == "F5") {
                event.key = Qt::Key_F5;
            } else if (event.text.toUpper() == "F6") {
                event.key = Qt::Key_F6;
            } else if (event.text.toUpper() == "F7") {
                event.key = Qt::Key_F7;
            } else if (event.text.toUpper() == "F8") {
                event.key = Qt::Key_F8;
            } else if (event.text.toUpper() == "F9") {
                event.key = Qt::Key_F9;
            } else if (event.text.toUpper() == "F10") {
                event.key = Qt::Key_F10;
            } else if (event.text.toUpper() == "F11") {
                event.key = Qt::Key_F11;
            } else if (event.text.toUpper() == "F12") {
                event.key = Qt::Key_F12;
            } else if (event.text.toUpper() == "UP") {
                event.key = Qt::Key_Up;
                event.isKeypad = true;
            } else if (event.text.toUpper() == "DOWN") {
                event.key = Qt::Key_Down;
                event.isKeypad = true;
            } else if (event.text.toUpper() == "LEFT") {
                event.key = Qt::Key_Left;
                event.isKeypad = true;
            } else if (event.text.toUpper() == "RIGHT") {
                event.key = Qt::Key_Right;
                event.isKeypad = true;
            } else if (event.text.toUpper() == "SPACE") {
                event.key = Qt::Key_Space;
            } else if (event.text.toUpper() == "ESC") {
                event.key = Qt::Key_Escape;
            } else if (event.text.toUpper() == "TAB") {
                event.key = Qt::Key_Tab;
            } else if (event.text.toUpper() == "DELETE") {
                event.key = Qt::Key_Delete;
            } else if (event.text.toUpper() == "BACKSPACE") {
                event.key = Qt::Key_Backspace;
            } else if (event.text.toUpper() == "SHIFT") {
                event.key = Qt::Key_Shift;
            } else if (event.text.toUpper() == "ALT") {
                event.key = Qt::Key_Alt;
            } else if (event.text.toUpper() == "CONTROL") {
                event.key = Qt::Key_Control;
            } else if (event.text.toUpper() == "META") {
                event.key = Qt::Key_Meta;
            } else if (event.text.toUpper() == "PAGE DOWN") {
                event.key = Qt::Key_PageDown;
            } else if (event.text.toUpper() == "PAGE UP") {
                event.key = Qt::Key_PageUp;
            } else if (event.text.toUpper() == "HOME") {
                event.key = Qt::Key_Home;
            } else if (event.text.toUpper() == "END") {
                event.key = Qt::Key_End;
            } else if (event.text.toUpper() == "HELP") {
                event.key = Qt::Key_Help;
            } else if (event.text.toUpper() == "CAPS LOCK") {
                event.key = Qt::Key_CapsLock;
            } else {
                // Key values do not distinguish between uppercase and lowercase
                // and use the uppercase key value.
                event.key = event.text.toUpper().at(0).unicode();
            }
            event.isValid = true;
        }
    }
    
    QScriptValue isShifted = object.property("isShifted");
    if (isShifted.isValid()) {
        event.isShifted = isShifted.toVariant().toBool();
    } else {
        // if no isShifted was included, get it from the text
        QChar character = event.text.at(0);
        if (character.isLetter() && character.isUpper()) {
            event.isShifted = true;
        } else {
            // if it's a symbol, then attempt to detect shifted-ness
            if (QString("~!@#$%^&*()_+{}|:\"<>?").contains(character)) {
                event.isShifted = true;
            }
        }
    }
    
    
    const bool wantDebug = false;
    if (wantDebug) {
        qCDebug(scriptengine) << "event.key=" << event.key
        << " event.text=" << event.text
        << " event.isShifted=" << event.isShifted
        << " event.isControl=" << event.isControl
        << " event.isMeta=" << event.isMeta
        << " event.isAlt=" << event.isAlt
        << " event.isKeypad=" << event.isKeypad
        << " event.isAutoRepeat=" << event.isAutoRepeat;
    }
}