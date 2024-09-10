void
CQIllustratorAlignToolbar::
addWidgets()
{
  QBoxLayout *layout = qobject_cast<QBoxLayout *>(CQIllustratorToolbar::layout());

  QGridLayout *grid = new QGridLayout;
  grid->setMargin(0); grid->setSpacing(2);

  layout->addLayout(grid);

  //-----

  QTabWidget *tab = new QTabWidget;

  QFont font = tab->font();

  font.setPointSizeF(font.pointSizeF()*0.7);

  tab->setFont(font);

  //------

  alignw_ = new CQAlignButtons;

  tab->addTab(alignw_, "Align");

  connect(alignw_, SIGNAL(alignLeft()), this, SIGNAL(alignLeft()));
  connect(alignw_, SIGNAL(alignBottom()), this, SIGNAL(alignBottom()));
  connect(alignw_, SIGNAL(alignRight()), this, SIGNAL(alignRight()));
  connect(alignw_, SIGNAL(alignTop()), this, SIGNAL(alignTop()));
  connect(alignw_, SIGNAL(alignHorizontal()), this, SIGNAL(alignHorizontal()));
  connect(alignw_, SIGNAL(alignVertical()), this, SIGNAL(alignVertical()));

  connect(alignw_, SIGNAL(alignLeftPreview()), this, SIGNAL(alignLeftPreview()));
  connect(alignw_, SIGNAL(alignBottomPreview()), this, SIGNAL(alignBottomPreview()));
  connect(alignw_, SIGNAL(alignRightPreview()), this, SIGNAL(alignRightPreview()));
  connect(alignw_, SIGNAL(alignTopPreview()), this, SIGNAL(alignTopPreview()));
  connect(alignw_, SIGNAL(alignHorizontalPreview()), this, SIGNAL(alignHorizontalPreview()));
  connect(alignw_, SIGNAL(alignVerticalPreview()), this, SIGNAL(alignVerticalPreview()));

  connect(alignw_, SIGNAL(alignPreviewClear()), this, SIGNAL(alignPreviewClear()));

  //------

  distw_ = new CQDistButtons;

  tab->addTab(distw_, "Distribute");

  //------

  spreadw_ = new CQSpreadButtons;

  tab->addTab(spreadw_, "Spread");

  //------

  grid->addWidget(tab, 0, 0, 2, 1);

  //------

  QLabel *olabel = new QLabel("<small><b>Offset</b></small>");

  offset_ = new CQRealEdit(0.0);

  offset_->setFocusPolicy(Qt::ClickFocus);

  grid->addWidget(olabel , 0, 1);
  grid->addWidget(offset_, 1, 1);

  //------

  anchor_ = new CQAlignAnchor;

  connect(anchor_, SIGNAL(selectObject()), this, SIGNAL(selectAnchorObject()));
  connect(anchor_, SIGNAL(selectPosition()), this, SIGNAL(selectAnchorPosition()));
  connect(anchor_, SIGNAL(cancelSelect()), this, SIGNAL(cancelSelectAnchor()));

  grid->addWidget(anchor_, 0, 2, 2, 1);

  //------

  grid->setColumnStretch(3, 1);
}