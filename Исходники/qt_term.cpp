// Called when terminal type is selected.
// This procedure should parse options on the command line.
// A list of the currently selected options should be stored in term_options[],
// in a form suitable for use with the set term command.
// term_options[] is used by the save command.  Use options_null() if no options are available." *
void qt_options()
{
	char *s = NULL;
	QString fontSettings;
	bool duplication = false;
	bool set_enhanced = false, set_font = false;
	bool set_persist = false, set_number = false;
	bool set_raise = false, set_ctrl = false;
	bool set_title = false, set_close = false;
	bool set_size = false;
	bool set_widget = false;
	bool set_dash = false;

	if (term_interlock != NULL && term_interlock != (void *)qt_init) {
		term = NULL;
		int_error(NO_CARET, "The qt terminal cannot be used in a wxt session");
	}

#define SETCHECKDUP(x) { c_token++; if (x) duplication = true; x = true; }

	while (!END_OF_COMMAND)
	{
		FPRINTF((stderr, "processing token\n"));
		switch (lookup_table(&qt_opts[0], c_token)) {
		case QT_WIDGET:
			SETCHECKDUP(set_widget);
			if (!(s = try_to_get_string()))
				int_error(c_token, "widget: expecting string");
			if (*s)
				qt_optionWidget = QString(s);
			free(s);
			break;
		case QT_FONT:
			SETCHECKDUP(set_font);
			if (!(s = try_to_get_string()))
				int_error(c_token, "font: expecting string");
			if (*s)
			{
				fontSettings = QString(s);
				QStringList list = fontSettings.split(',');
				if ((list.size() > 0) && !list[0].isEmpty())
					qt_optionFontName = list[0];
				if ((list.size() > 1) && (list[1].toInt() > 0))
					qt_optionFontSize = list[1].toInt();
			}
			free(s);
			break;
		case QT_ENHANCED:
			SETCHECKDUP(set_enhanced);
			qt_optionEnhanced = true;
			term->flags |= TERM_ENHANCED_TEXT;
			break;
		case QT_NOENHANCED:
			SETCHECKDUP(set_enhanced);
			qt_optionEnhanced = false;
			term->flags &= ~TERM_ENHANCED_TEXT;
			break;
		case QT_SIZE:
			SETCHECKDUP(set_size);
			if (END_OF_COMMAND)
				int_error(c_token, "size requires 'width,heigth'");
			qt_optionWidth = real_expression();
			if (!equals(c_token++, ","))
				int_error(c_token, "size requires 'width,heigth'");
			qt_optionHeight = real_expression();
			if (qt_optionWidth < 1 || qt_optionHeight < 1)
				int_error(c_token, "size is out of range");
			break;
		case QT_PERSIST:
			SETCHECKDUP(set_persist);
			qt_optionPersist = true;
			break;
		case QT_NOPERSIST:
			SETCHECKDUP(set_persist);
			qt_optionPersist = false;
			break;
		case QT_RAISE:
			SETCHECKDUP(set_raise);
			qt_optionRaise = true;
			break;
		case QT_NORAISE:
			SETCHECKDUP(set_raise);
			qt_optionRaise = false;
			break;
		case QT_CTRL:
			SETCHECKDUP(set_ctrl);
			qt_optionCtrl = true;
			break;
		case QT_NOCTRL:
			SETCHECKDUP(set_ctrl);
			qt_optionCtrl = false;
			break;
		case QT_TITLE:
			SETCHECKDUP(set_title);
			if (!(s = try_to_get_string()))
				int_error(c_token, "title: expecting string");
			if (*s)
				qt_optionTitle = qt_codec->toUnicode(s);
			free(s);
			break;
		case QT_CLOSE:
			SETCHECKDUP(set_close);
			break;
		case QT_DASH:
			SETCHECKDUP(set_dash);
			qt_optionDash = true;
			break;
		case QT_SOLID:
			SETCHECKDUP(set_dash);
			qt_optionDash = false;
			break;
		case QT_OTHER:
		default:
			qt_optionWindowId = int_expression();
			qt_optionWidget = "";
			if (set_number) duplication = true;
			set_number = true;
			break;
		}

		if (duplication)
			int_error(c_token-1, "Duplicated or contradicting arguments in qt term options.");
	}

	// Save options back into options string in normalized format
	QString termOptions = QString::number(qt_optionWindowId);

	/* Initialize user-visible font setting */
	fontSettings = qt_optionFontName + "," + QString::number(qt_optionFontSize);

	if (set_title)
	{
		termOptions += " title \"" + qt_optionTitle + '"';
		if (qt_initialized)
			qt_out << GETitle << qt_optionTitle;
	}

	if (set_size)
	{
		termOptions += " size " + QString::number(qt_optionWidth) + ", "
		                        + QString::number(qt_optionHeight);
		qt_setSize   = true;
		qt_setWidth  = qt_optionWidth;
		qt_setHeight = qt_optionHeight;
	}

	if (set_enhanced) termOptions +=  qt_optionEnhanced ? " enhanced" : " noenhanced";
	                  termOptions += " font \"" + fontSettings + '"';
	if (set_dash)     termOptions += qt_optionDash ? " dashed" : " solid";
	if (set_widget)   termOptions += " widget \"" + qt_optionWidget + '"';
	if (set_persist)  termOptions += qt_optionPersist ? " persist" : " nopersist";
	if (set_raise)    termOptions += qt_optionRaise ? " raise" : " noraise";
	if (set_ctrl)     termOptions += qt_optionCtrl ? " ctrl" : " noctrl";

	if (set_close && qt_initialized) qt_out << GECloseWindow << qt_optionWindowId;

	/// @bug change Utf8 to local encoding
	strncpy(term_options, termOptions.toUtf8().data(), MAX_LINE_LEN);
}