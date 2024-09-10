FunctionViewer::FunctionViewer(QWidget *parent, Qt::WFlags flags)
#endif
    : QSplitter(parent)
    , m_xshHandle(0)
    , m_frameHandle(0)
    , m_objectHandle(0)
    , m_fxHandle(0)
    , m_columnHandle(0)
    , m_curve(0)
    , m_selection(new FunctionSelection())
    , m_sceneHandle(0) {
  setObjectName("FunctionEditor");

  // Prepare local timeline
  m_localFrame.setFrame(0);
  setFocusPolicy(Qt::NoFocus);

  m_treeView         = new FunctionTreeView(this);
  m_functionGraph    = new FunctionPanel(this);
  m_numericalColumns = new FunctionSheet();
  m_toolbar          = new FunctionToolbar;
  m_segmentViewer =
      new FunctionSegmentViewer(this, m_numericalColumns, m_functionGraph);
  QWidget *leftPanel  = new QWidget();
  QWidget *rightPanel = new QWidget();

  //----
  m_treeView->resize(150, m_treeView->size().height());
  m_treeView->setMinimumWidth(0);

  FunctionTreeModel *ftModel =
      dynamic_cast<FunctionTreeModel *>(m_treeView->model());
  m_functionGraph->setModel(ftModel);
  m_numericalColumns->setModel(ftModel);

  m_functionGraph->setSelection(getSelection());
  m_numericalColumns->setSelection(getSelection());

  m_numericalColumns->setViewer(this);

  m_toolbar->setSelection(m_selection);
  m_toolbar->setFocusPolicy(Qt::NoFocus);

  m_toolbar->setFrameHandle(
      &m_localFrame);  // The function editor adopts an internal timeline
  m_functionGraph->setFrameHandle(
      &m_localFrame);  // synchronized among its various sub-widgets.
  m_numericalColumns->setFrameHandle(
      &m_localFrame);  // In case an external m_frameHandle is specified,
                       // it synchronizes with that, too.

  //---- layout

  QVBoxLayout *leftLayout = new QVBoxLayout();
  leftLayout->setMargin(0);
  leftLayout->setSpacing(0);
  {
    leftLayout->addWidget(m_toolbar);
    leftLayout->addSpacing(36);
    leftLayout->addWidget(m_numericalColumns);
  }
  leftPanel->setLayout(leftLayout);

  addWidget(leftPanel);

  QVBoxLayout *rightLayout = new QVBoxLayout();
  rightLayout->setMargin(0);
  rightLayout->setSpacing(5);
  {
    rightLayout->addWidget(m_segmentViewer, 0);
    rightLayout->addWidget(m_treeView, 1);
  }
  rightPanel->setLayout(rightLayout);

  addWidget(rightPanel);

  //--- set the splitter's default size
  setSizes(QList<int>() << 500 << 200);
  setStretchFactor(0, 5);
  setStretchFactor(1, 2);

  //---- signal-slot connections
  bool ret = true;
  ret      = ret && connect(m_toolbar, SIGNAL(numericalColumnToggled()), this,
                       SLOT(toggleMode()));
  ret = ret && connect(ftModel, SIGNAL(activeChannelsChanged()),
                       m_functionGraph, SLOT(update()));
  ret = ret && connect(ftModel, SIGNAL(activeChannelsChanged()),
                       m_numericalColumns, SLOT(updateAll()));
  ret = ret && connect(ftModel, SIGNAL(curveChanged(bool)), m_treeView,
                       SLOT(update()));
  ret = ret && connect(ftModel, SIGNAL(curveChanged(bool)), m_functionGraph,
                       SLOT(update()));
  ret = ret && connect(ftModel, SIGNAL(curveChanged(bool)), m_numericalColumns,
                       SLOT(updateAll()));
  ret = ret && connect(ftModel, SIGNAL(curveSelected(TDoubleParam *)), this,
                       SLOT(onCurveSelected(TDoubleParam *)));
  ret = ret && connect(ftModel, SIGNAL(curveChanged(bool)), m_segmentViewer,
                       SLOT(onCurveChanged()));
  ret = ret && connect(ftModel, SIGNAL(curveChanged(bool)), this,
                       SLOT(onCurveChanged(bool)));
  ret = ret && connect(&m_localFrame, SIGNAL(frameSwitched()), this,
                       SLOT(onFrameSwitched()));
  ret = ret && connect(getSelection(), SIGNAL(selectionChanged()), this,
                       SLOT(onSelectionChanged()));
  ret = ret && connect(m_functionGraph, SIGNAL(keyframeSelected(double)),
                       m_toolbar, SLOT(setFrame(double)));

  ret = ret && connect(m_treeView, SIGNAL(switchCurrentObject(TStageObject *)),
                       this, SLOT(doSwitchCurrentObject(TStageObject *)));
  ret = ret && connect(m_treeView, SIGNAL(switchCurrentFx(TFx *)), this,
                       SLOT(doSwitchCurrentFx(TFx *)));

  ret = ret &&
        connect(ftModel,
                SIGNAL(currentChannelChanged(FunctionTreeModel::Channel *)),
                m_numericalColumns,
                SLOT(onCurrentChannelChanged(FunctionTreeModel::Channel *)));

  assert(ret);

  m_functionGraph->hide();
}