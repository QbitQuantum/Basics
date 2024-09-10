EditStyle::EditStyle(Score* s, QWidget* parent)
   : QDialog(parent)
      {
      setupUi(this);
      setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
      cs     = s;

      buttonApplyToAllParts = buttonBox->addButton(tr("Apply to all Parts"), QDialogButtonBox::ApplyRole);
      buttonApplyToAllParts->setEnabled(cs->parentScore() != nullptr);

      lstyle = *s->style();
      setModal(true);

      chordDescriptionFileButton->setIcon(*icons[int(Icons::fileOpen_ICON)]);

      pageList->setCurrentRow(0);

      //articulationTable->verticalHeader()->setVisible(false); // can get disabled in ui file
      articulationTable->setSelectionBehavior(QAbstractItemView::SelectRows);
      QStringList headers;
      headers << tr("Symbol") << tr("Anchor");
      articulationTable->setHorizontalHeaderLabels(headers);
      articulationTable->setColumnWidth(0, 200);
      articulationTable->setColumnWidth(1, 180);
      articulationTable->setRowCount(int(ArticulationType::ARTICULATIONS));

      accidentalsGroup->setVisible(false); // disable, not yet implemented

      musicalSymbolFont->clear();
      int idx = 0;
      for (auto i : ScoreFont::scoreFonts()) {
            musicalSymbolFont->addItem(i.name(), idx);
            ++idx;
            }

      for (int i = 0; i < int(ArticulationType::ARTICULATIONS); ++i) {
            ArticulationInfo* ai = &Articulation::articulationList[i];

            QPixmap ct = cs->scoreFont()->sym2pixmap(ai->upSym, 3.0);
            QIcon icon(ct);
            QTableWidgetItem* item = new QTableWidgetItem(icon, qApp->translate("articulation", qPrintable(ai->description)));

            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            articulationTable->setItem(i, 0, item);

            QComboBox* cb = new QComboBox();
            cb->addItem(tr("Above Staff"), int(ArticulationAnchor::TOP_STAFF));
            cb->addItem(tr("Below Staff"), int(ArticulationAnchor::BOTTOM_STAFF));
            cb->addItem(tr("Chord Automatic"), int(ArticulationAnchor::CHORD));
            cb->addItem(tr("Above Chord"), int(ArticulationAnchor::TOP_CHORD));
            cb->addItem(tr("Below Chord"), int(ArticulationAnchor::BOTTOM_CHORD));
            articulationTable->setCellWidget(i, 1, cb);
            }
      QButtonGroup* bg = new QButtonGroup(this);
      bg->addButton(editEvenHeaderL, 0);
      bg->addButton(editEvenHeaderC, 1);
      bg->addButton(editEvenHeaderR, 2);
      bg->addButton(editOddHeaderL,  3);
      bg->addButton(editOddHeaderC,  4);
      bg->addButton(editOddHeaderR,  5);

      bg->addButton(editEvenFooterL, 6);
      bg->addButton(editEvenFooterC, 7);
      bg->addButton(editEvenFooterR, 8);
      bg->addButton(editOddFooterL,  9);
      bg->addButton(editOddFooterC, 10);
      bg->addButton(editOddFooterR, 11);

      // figured bass init
      QList<QString> fbFontNames = FiguredBass::fontNames();
      foreach(const QString& family, fbFontNames)
            comboFBFont->addItem(family);
      comboFBFont->setCurrentIndex(0);
      connect(comboFBFont, SIGNAL(currentIndexChanged(int)), SLOT(on_comboFBFont_currentIndexChanged(int)));

      setValues();

      // keep in sync with implementation in Page::replaceTextMacros (page.cpp)
      // jumping thru hoops here to make the job of translators easier, yet have a nice display
      QString toolTipHeaderFooter
            = QString("<html><head></head><body><p><b>")
            + tr("Special symbols in header/footer")
            + QString("</b></p>")
            + QString("<table><tr><td>$p</td><td>-</td><td><i>")
            + tr("page number, except on first page")
            + QString("</i></td></tr><tr><td>$P</td><td>-</td><td><i>")
            + tr("page number, on all pages")
            + QString("</i></td></tr><tr><td>$n</td><td>-</td><td><i>")
            + tr("number of pages")
            + QString("</i></td></tr><tr><td>$f</td><td>-</td><td><i>")
            + tr("file name")
            + QString("</i></td></tr><tr><td>$F</td><td>-</td><td><i>")
            + tr("file path+name")
            + QString("</i></td></tr><tr><td>$d</td><td>-</td><td><i>")
            + tr("current date")
            + QString("</i></td></tr><tr><td>$D</td><td>-</td><td><i>")
            + tr("creation date")
            + QString("</i></td></tr><tr><td>$C</td><td>-</td><td><i>")
            + tr("copyright, on first page only")
            + QString("</i></td></tr><tr><td>$c</td><td>-</td><td><i>")
            + tr("copyright, on all pages")
            + QString("</i></td></tr><tr><td>$$</td><td>-</td><td><i>")
            + tr("the $ sign itself")
            + QString("</i></td></tr><tr><td>$:tag:</td><td>-</td><td><i>")
            + tr("meta data tag")
            + QString("</i></td></tr></table><p>")
            + tr("Available tags and their current values:")
            + QString("</p><table>");
      // shown all tags for curent score, see also Score::init()
      QMapIterator<QString, QString> i(cs->metaTags());
      while (i.hasNext()) {
            i.next();
            toolTipHeaderFooter += QString("<tr><td>%1</td><td>-</td><td>%2</td></tr>").arg(i.key()).arg(i.value());
      }
      toolTipHeaderFooter += QString("</table></body></html>");
      showHeader->setToolTip(toolTipHeaderFooter);
      showFooter->setToolTip(toolTipHeaderFooter);
      connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), SLOT(buttonClicked(QAbstractButton*)));
      connect(headerOddEven, SIGNAL(toggled(bool)), SLOT(toggleHeaderOddEven(bool)));
      connect(footerOddEven, SIGNAL(toggled(bool)), SLOT(toggleFooterOddEven(bool)));
      connect(chordDescriptionFileButton, SIGNAL(clicked()), SLOT(selectChordDescriptionFile()));
      connect(chordsStandard, SIGNAL(toggled(bool)), SLOT(setChordStyle(bool)));
      connect(chordsJazz, SIGNAL(toggled(bool)), SLOT(setChordStyle(bool)));
      connect(chordsCustom, SIGNAL(toggled(bool)), SLOT(setChordStyle(bool)));
      connect(SwingOff, SIGNAL(toggled(bool)), SLOT(setSwingParams(bool)));
      connect(swingEighth, SIGNAL(toggled(bool)), SLOT(setSwingParams(bool)));
      connect(swingSixteenth, SIGNAL(toggled(bool)), SLOT(setSwingParams(bool)));
      connect(hideEmptyStaves, SIGNAL(clicked(bool)), dontHideStavesInFirstSystem, SLOT(setEnabled(bool)));

      connect(bg, SIGNAL(buttonClicked(int)), SLOT(editTextClicked(int)));

      QSignalMapper* mapper = new QSignalMapper(this);

#define CR(W, ID) connect(W, SIGNAL(clicked()), mapper, SLOT(map())); mapper->setMapping(W, int(ID));
      CR(resetVoltaY,                StyleIdx::voltaY);
      CR(resetVoltaHook,             StyleIdx::voltaHook);
      CR(resetVoltaLineWidth,        StyleIdx::voltaLineWidth);
      CR(resetVoltaLineStyle,        StyleIdx::voltaLineStyle);

      CR(resetOttavaY,               StyleIdx::ottavaY);
      CR(resetOttavaHook,            StyleIdx::ottavaHook);
      CR(resetOttavaLineWidth,       StyleIdx::ottavaLineWidth);
      CR(resetOttavaLineStyle,       StyleIdx::ottavaLineStyle);
      CR(resetOttavaNumbersOnly,     StyleIdx::ottavaNumbersOnly);

      CR(resetHairpinY,              StyleIdx::hairpinY);
      CR(resetHairpinLineWidth,      StyleIdx::hairpinLineWidth);
      CR(resetHairpinHeight,         StyleIdx::hairpinHeight);
      CR(resetHairpinContinueHeight, StyleIdx::hairpinContHeight);
#undef CR
      connect(mapper, SIGNAL(mapped(int)), SLOT(resetStyleValue(int)));

      }