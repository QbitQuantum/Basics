QucsEdit::QucsEdit(const QString& FileName_, bool readOnly)
{
  // set application icon
  setIcon (QPixmap(QucsSettings.BitmapDir + "big.qucs.xpm"));
  setCaption("Qucs Editor " PACKAGE_VERSION " - " + tr("File: "));

  QVBoxLayout *v = new QVBoxLayout(this);

  QHBox *h = new QHBox(this);
  v->addWidget(h);

  QToolButton *ButtLoad = new QToolButton(h);
  ButtLoad->setIconSet(
	    QIconSet(QImage(QucsSettings.BitmapDir + "fileopen.png")));
  connect(ButtLoad, SIGNAL(clicked()), SLOT(slotLoad()));

  QToolButton *ButtSave = new QToolButton(h);
  ButtSave->setIconSet(
            QIconSet(QImage(QucsSettings.BitmapDir + "filesave.png")));
  connect(ButtSave, SIGNAL(clicked()), SLOT(slotSave()));
  ButtSave->setDisabled(readOnly);

  h->setStretchFactor(new QWidget(h),5); // stretchable placeholder
  PosText = new QLabel(tr("Line: %1  -  Column: %2").arg(1).arg(1), h);
  h->setStretchFactor(new QWidget(h),5); // stretchable placeholder

  QPushButton *ButtAbout = new QPushButton(tr("About"),h);
  connect(ButtAbout, SIGNAL(clicked()), SLOT(slotAbout()));

  QPushButton *ButtOK = new QPushButton(tr("Quit"),h);
  connect(ButtOK, SIGNAL(clicked()), SLOT(slotQuit()));
  ButtOK->setFocus();

  // try using same-sized mono-spaced font in the textarea
  QFont fedit = QFont("Courier New");
  fedit.setPointSize(QucsSettings.font.pointSize()-1);
  fedit.setStyleHint(QFont::Courier);
  fedit.setFixedPitch(true);

  text = new QTextEdit(this);
  text->setTextFormat(Qt::PlainText);
  text->setReadOnly(readOnly);
  text->setWordWrap(QTextEdit::NoWrap);
  text->setMinimumSize(300,200);
  text->setFont(fedit);
  text->setCurrentFont(fedit);
  v->addWidget(text);
  connect(text, SIGNAL(cursorPositionChanged(int, int)),
          SLOT(slotPrintCursorPosition(int, int)));

  // .................................................
  loadFile(FileName_);
}