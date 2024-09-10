TextPalette::TextPalette(QWidget* parent)
   : QWidget(parent)
      {
      setWindowFlags(Qt::Tool);
      setupUi(this);

      pCommon = new Palette;
      pCommon->setMag(0.8);
      pCommon->setGrid(33, 60);
      pCommon->setReadOnly(true);

      pSmufl = new Palette;
      pSmufl->setMag(0.8);
      pSmufl->setGrid(33, 60);
      pSmufl->setReadOnly(true);

      pUnicode = new Palette;
      pUnicode->setMag(0.8);
      pUnicode->setGrid(33, 60);
      pUnicode->setReadOnly(true);

      PaletteScrollArea* psa = new PaletteScrollArea(pCommon);
      psa->setRestrictHeight(false);

      tabWidget->clear();
      tabWidget->addTab(psa, tr("Common Symbols"));

      psa = new PaletteScrollArea(pSmufl);
      psa->setRestrictHeight(false);

      QSplitter* ws = new QSplitter;
      lws = new QListWidget;

      ScoreFont* scoreFont = ScoreFont::fontFactory("Bravura");
      QFile fi(scoreFont->fontPath() + "ranges.json");
      if (!fi.open(QIODevice::ReadOnly))
            qDebug("ScoreFont: open ranges file <%s> failed", qPrintable(fi.fileName()));
      QJsonParseError error;
      QJsonObject o = QJsonDocument::fromJson(fi.readAll(), &error).object();
      if (error.error != QJsonParseError::NoError)
            qDebug("Json parse error in <%s>(offset: %d): %s", qPrintable(fi.fileName()),
               error.offset, qPrintable(error.errorString()));
	int i = 0;
      QStringList smuflRangeNames;
      for (auto s : o.keys()) {
            QJsonObject range = o.value(s).toObject();
            QString desc = range.value("description").toString();
            QJsonArray glyphs = range.value("glyphs").toArray();
            if (glyphs.size() > 0) {
                  for (QJsonValue g : glyphs)
                        smuflMap[i].append(g.toString());
                  smuflRangeNames.append(desc);
                  i++;
                  }
            }

      lws->addItems(smuflRangeNames);
      lws->setCurrentRow(0);

      ws->addWidget(lws);
      ws->addWidget(psa);

      tabWidget->addTab(ws, tr("Musical Symbols"));

      psa = new PaletteScrollArea(pUnicode);
      psa->setRestrictHeight(false);

      QSplitter* wu = new QSplitter;
      lwu = new QListWidget;
      lwu->setSortingEnabled(true);
      for (i = 0; i < unicodeRangeNames.length(); i++) {
            QListWidgetItem* newItem = new QListWidgetItem(qApp->translate("accidental", unicodeRangeNames.at(i).toUtf8().constData()));
            newItem->setData(Qt::UserRole, i);
            lwu->addItem(newItem);
            if (i == 0)
                  lwu->setCurrentItem(newItem);
            }

      wu->addWidget(lwu);
      wu->addWidget(psa);

      tabWidget->addTab(wu, tr("Unicode Symbols"));

      connect(lws, SIGNAL(currentRowChanged(int)), SLOT(populateSmufl()));
      connect(lwu, SIGNAL(currentRowChanged(int)), SLOT(populateUnicode()));

	// others are done in setFont
      populateSmufl();

      setFocusPolicy(Qt::NoFocus);
      }