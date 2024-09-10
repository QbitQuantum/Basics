bool DocumentEditor::load(const QString &fileName_) {
	QFile file(fileName_);
	if (!file.open(QFile::ReadOnly)) {
		QMessageBox::warning(this, PACKAGE_NAME,
							 tr("Cannot read file %1:\n%2.")
							 .arg(fileName_)
							 .arg(file.errorString()));
		return false;
	}

	///@todo better charset detection
	char bom[6];
	file.read(bom, 6);
	file.reset();
	detectBOM(bom);

	QString shebang;
	for(uint8_t i = 0; i < 5; i++){
		if(bom[i] == '#'){
			if(bom[i+1] == '!'){
				char line[80];
				file.readLine(line, 80);
				file.reset();
				shebang = line;
			}
		}
	}

	QTextCodec* codec = QTextCodec::codecForName(_codec.toUtf8());
	if(codec == 0) {
		QMessageBox::critical(this, PACKAGE_NAME,
							  tr("Cannot load file %1:\nUnsupported charset %2 !!")
							  .arg(fileName_).arg(_codec));
		return false;
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);

	QString data = codec->toUnicode(file.readAll());
	setText(data);

	_fullPath = fileName_;
	_isNew = false;
	setModified(false);

	if(_autoDetectEol)
		autoDetectEol();
	if(_autoDetectIndent)
		autoDetectIndent();

	//add lexer
	QsciLexer* l = lexer();
	//detach lexer from document before delete it
	setLexer(0);
	if(l != 0) {
		delete l;
		l = 0;
	}
	setLexer(LexerManager::getInstance().getAutoLexer(this, shebang));

	//reload settings for lexer
	Settings settings;
	settings.applyToDocument(this);

	//add it to the watcher
	_watcher.addPath(_fullPath);

	QApplication::restoreOverrideCursor();
	_notified = true;

	return true;
}