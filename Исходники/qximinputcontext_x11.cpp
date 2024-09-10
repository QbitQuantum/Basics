    static int xic_draw_callback(XIC, XPointer client_data, XPointer call_data) {
	QXIMInputContext *qic = (QXIMInputContext *) client_data;
	if (!qic) {
	    XIM_DEBUG("xic_draw_callback: no qic");
	    return 0;
	}
        QXIMInputContext::ICData *data = qic->icData();
	if (!data) {
	    XIM_DEBUG("xic_draw_callback: no ic data");
	    return 0;
	}
        XIM_DEBUG("xic_draw_callback");


	if(!data->composing) {
	    data->clear();
            data->composing = true;
        }

	XIMPreeditDrawCallbackStruct *drawstruct = (XIMPreeditDrawCallbackStruct *) call_data;
	XIMText *text = (XIMText *) drawstruct->text;
	int cursor = drawstruct->caret, sellen = 0, selstart = 0;

	if (!drawstruct->caret && !drawstruct->chg_first && !drawstruct->chg_length && !text) {
	    if(data->text.isEmpty()) {
		XIM_DEBUG("compose emptied");
		// if the composition string has been emptied, we need
		// to send an InputMethodEnd event
                QInputMethodEvent e;
		qic->sendEvent(e);
		data->clear();

		// if the commit string has coming after here, InputMethodStart
		// will be sent dynamically
	    }
	    return 0;
	}

	if (text) {
	    char *str = 0;
	    if (text->encoding_is_wchar) {
		int l = wcstombs(NULL, text->string.wide_char, text->length);
		if (l != -1) {
		    str = new char[l + 1];
		    wcstombs(str, text->string.wide_char, l);
		    str[l] = 0;
		}
	    } else
		str = text->string.multi_byte;

	    if (!str)
		return 0;

	    QString s = QString::fromLocal8Bit(str);

	    if (text->encoding_is_wchar)
		delete [] str;

	    if (drawstruct->chg_length < 0)
		data->text.replace(drawstruct->chg_first, INT_MAX, s);
	    else
		data->text.replace(drawstruct->chg_first, drawstruct->chg_length, s);

	    if (data->selectedChars.size() < data->text.length()) {
		// expand the selectedChars array if the compose string is longer
		int from = data->selectedChars.size();
		data->selectedChars.resize(data->text.length());
                for (int x = from; x < data->selectedChars.size(); ++x)
                    data->selectedChars.clearBit(x);
	    }

            // determine if the changed chars are selected based on text->feedback
            for (int x = 0; x < text->length; ++x)
                data->selectedChars.setBit(x + drawstruct->chg_first,
                                           (text->feedback ? (text->feedback[x] & XIMReverse) : 0));

            // figure out where the selection starts, and how long it is
            bool started = false;
            for (int x = 0; x < qMin(data->selectedChars.size(), data->text.length()); ++x) {
                if (started) {
                    if (data->selectedChars.testBit(x)) ++sellen;
                    else break;
                } else {
                    if (data->selectedChars.testBit(x)) {
                        selstart = x;
                        started = true;
                        sellen = 1;
                    }
                }
            }
	} else {
	    if (drawstruct->chg_length == 0)
		drawstruct->chg_length = -1;

	    data->text.remove(drawstruct->chg_first, drawstruct->chg_length);
	    bool qt_compose_emptied = data->text.isEmpty();
	    if (qt_compose_emptied) {
		XIM_DEBUG("compose emptied 2 text=%s", data->text.toUtf8().constData());
		// if the composition string has been emptied, we need
		// to send an InputMethodEnd event
                QInputMethodEvent e;
		qic->sendEvent(e);
		data->clear();
		// if the commit string has coming after here, InputMethodStart
		// will be sent dynamically
		return 0;
	    }
	}

        XIM_DEBUG("sending compose: '%s', cursor=%d, sellen=%d",
                  data->text.toUtf8().constData(), cursor, sellen);
        QList<QInputMethodEvent::Attribute> attrs;
        if (selstart > 0)
            attrs << QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat, 0, selstart,
                                                  qic->standardFormat(QInputContext::PreeditFormat));
        if (sellen)
            attrs << QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat, selstart, sellen,
                                                  qic->standardFormat(QInputContext::SelectionFormat));
        if (selstart + sellen < data->text.length())
            attrs << QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat,
                                                  selstart + sellen, data->text.length() - selstart - sellen,
                                                  qic->standardFormat(QInputContext::PreeditFormat));
        attrs << QInputMethodEvent::Attribute(QInputMethodEvent::Cursor, cursor, sellen ? 0 : 1, QVariant());
        QInputMethodEvent e(data->text, attrs);
        data->preeditEmpty = data->text.isEmpty();
	qic->sendEvent(e);

	return 0;
    }