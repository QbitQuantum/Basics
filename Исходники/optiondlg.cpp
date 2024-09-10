/* 
 *  Constructs a OptionDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
OptionDlg::OptionDlg( QWidget* parent,  const char* name, WFlags fl )
    : OptionForm( parent, name, fl )
{
  connect(m_btnOK, SIGNAL(clicked()), this, SLOT(updateSettings()));
  connect(m_btnCancel, SIGNAL(clicked()), this, SIGNAL(endDialog()));

  // font option ( check OptionDlg::updateExFont method );
  m_wFonts->insertItem(tr("Default Font"), 0);
  //m_wFonts->insertItem("Progress Bar", 1);

  // color option ( check OptionDlg::updateExColor method )
  m_wColors->insertItem(tr("Background"), 0);
  m_wColors->insertItem(tr("Normal Text"), 1);
  m_wColors->insertItem(tr("HighLight Text 1"), 2);
  m_wColors->insertItem(tr("HighLight Text 2"), 3);
  m_wColors->insertItem(tr("HighLight Text 3"), 4);
  m_wColors->insertItem(tr("HighLight Text 4"), 5);
  m_wColors->insertItem(tr("HighLight Text 5"), 6);
  m_wColors->insertItem(tr("HighLight Text 6"), 7);
  m_wColors->insertItem(tr("HighLight Text 7"), 8);
  m_wColors->insertItem(tr("Progress Bar FG"), 9);
  m_wColors->insertItem(tr("Progress Bar BG"), 10);
  m_wColors->insertItem(tr("Progress Bar Text"), 11);

  m_wFontName->insertStringList(QFontDatabase().families());

  connect(m_wFontName, SIGNAL(activated(int)), this, SLOT(updateFontFace()));
  connect(m_wFontSize, SIGNAL(valueChanged(int)), this, SLOT(updateFontFace()));
  connect(m_wFonts, SIGNAL(activated(int)), this, SLOT(changeFont()));
  connect(m_wBold, SIGNAL(toggled(bool)), this, SLOT(updateFontFace()));
  connect(m_wFakeBold, SIGNAL(toggled(bool)), this, SLOT(updateFontFace()));

  connect(m_wColors, SIGNAL(activated(int)), this, SLOT(changeColor()));
  connect(m_wColorEdit, SIGNAL(returnPressed()), this, SLOT(updateColorFace()));
  connect(m_wRed, SIGNAL(valueChanged(int)), this, SLOT(rgbChange()));
  connect(m_wGreen, SIGNAL(valueChanged(int)), this, SLOT(rgbChange()));
  connect(m_wBlue, SIGNAL(valueChanged(int)), this, SLOT(rgbChange()));

  connect(m_wMargin, SIGNAL(valueChanged(int)), this, SLOT(updateMargin(int)));
  connect(m_wLineMargin, SIGNAL(valueChanged(int)),
                                      this, SLOT(updateLineMargin(int)));
  connect(m_wRotation, SIGNAL(valueChanged(int)),
                                      this, SLOT(updateRotation(int)));
  connect(m_wShowBar, SIGNAL(toggled(bool)),
                                      this, SLOT(updateBar()));
  connect(m_wBarHeight, SIGNAL(valueChanged(int)),
                                      this, SLOT(updateBar()));

  connect(m_wScrollHeight, SIGNAL(valueChanged(int)),
                                      this, SLOT(updateScrollHeight(int)));
  connect(m_wScrollDelay, SIGNAL(valueChanged(int)),
                                      this, SLOT(updateScrollDelay(int)));

  connect(m_wScalingMethod,SIGNAL(activated(int)),
      this, SLOT(updateScaleMethod(int)));
  connect(m_wScaleFactor,SIGNAL(valueChanged(int)),
      this, SLOT(updateScaleFactor(int)));
  connect(m_wScaleUp,SIGNAL(stateChanged(int)),
      this, SLOT(updateScaleUp(int)));
  connect(m_wHSlices,SIGNAL(valueChanged(int)),
      this, SLOT(updateSlicingCount()));
  connect(m_wVSlices,SIGNAL(valueChanged(int)),
      this, SLOT(updateSlicingCount()));

  connect(m_wScrollMethod,SIGNAL(activated(int)),
      this, SLOT(updateScrollPolicy(int)));
  connect(m_wPageMethod, SIGNAL(activated(int)),
      this, SLOT(updatePagingPolicy(int)));

  setFocusPolicy(QWidget::StrongFocus);

  m_cfg = NULL;
}