MLMakeBatchInspector::MLMakeBatchInspector(QWidget *parent)
  : AlgorithmInspector(parent)
{
  _type = AlgorithmManager::MLMakeBatch;

  // input
  QTabWidget *tabInput = new QTabWidget(this);
  _listImagery = new SourceList(
              ContentNode::LayerImagery, this);
  _listLabel = new SourceList(
              ContentNode::LayerLabelmap | ContentNode::LayerShape, this);
  _listROI = new SourceList(
              ContentNode::LayerShape, this);
  tabInput->addTab(_listImagery, "Imagery");
  tabInput->addTab(_listLabel, "Label");
  tabInput->addTab(_listROI, "ROI");
  GVBoxLayout *layInput = new GVBoxLayout;
  layInput->setContentsMargins(15, 0, 4, 4);
  layInput->addWidget(tabInput);
  ToggleGroup *groupInput = new ToggleGroup(this);
  groupInput->setTitle("Input");
  groupInput->addLayout(layInput);

  // params
  _valueBackground = new QSpinBox(this);
  _valueBackground->setMinimum(0);
  _valueBackground->setMaximum(255);
  _valueBackground->setValue(255);
  _valueBackground->setKeyboardTracking(false);
  _valueScale = new QSpinBox(this);
  _valueScale->setMinimum(1);
  _valueScale->setMaximum(4096);
  _valueScale->setValue(64);
  _valueScale->setKeyboardTracking(false);
  connect(_valueScale, SIGNAL(valueChanged(int)), this, SLOT(PreviewFrameScale(int)));
  GParamLayout *layParams2 = new GParamLayout;
  layParams2->setSpacing(_config_ui().INSPECTORVIEW_PARAM_SPACING);
  layParams2->setContentsMargins(
              _config_ui().INSPECTORVIEW_PARAM_MARGIN_LEFT,
              0,
              _config_ui().INSPECTORVIEW_PARAM_MARGIN_RIGHT,
              _config_ui().INSPECTORVIEW_PARAM_MARGIN_BOTTOM);
  layParams2->addParam(new TextLabel("Background Label"), _valueBackground, Qt::AlignRight);
  layParams2->addParam(new TextLabel("Scale"), _valueScale, Qt::AlignRight);
  ToggleGroup *groupParams = new ToggleGroup(this);
  groupParams->setTitle("Params");
  groupParams->addLayout(layParams2);

  // output
  _valueDBName = new FileEdit(this);
  connect(_valueDBName, SIGNAL(open()), this, SLOT(SetDBName()));
  GParamLayout *layOutput = new GParamLayout;
  layOutput->setSpacing(_config_ui().INSPECTORVIEW_PARAM_SPACING);
  layOutput->setContentsMargins(
              _config_ui().INSPECTORVIEW_PARAM_MARGIN_LEFT,
              _config_ui().INSPECTORVIEW_PARAM_MARGIN_TOP,
              _config_ui().INSPECTORVIEW_PARAM_MARGIN_RIGHT,
              _config_ui().INSPECTORVIEW_PARAM_MARGIN_BOTTOM);
  layOutput->addParam(new TextLabel("Output Dir"), _valueDBName);
  ToggleGroup *groupOutput = new ToggleGroup(this);
  groupOutput->setTitle("Output");
  groupOutput->addLayout(layOutput);

  // overall
  GVBoxLayout *layout = new GVBoxLayout;
  layout->addWidget(groupInput, 0);
  layout->addWidget(groupParams, 0);
  layout->addWidget(groupOutput, 0);
  layout->addStretch(1);
  layout->setSpacing(10);
  QWidget *cont = new QWidget(this);
  cont->setLayout(layout);

  // settings
  _area->setWidget(cont);
  _textAlgorithm->setText("Batch Making");
}