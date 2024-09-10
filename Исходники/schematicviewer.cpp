SchematicViewer::SchematicViewer(QWidget *parent)
	: QWidget(parent), m_fullSchematic(true), m_maximizedNode(false), m_sceneHandle(0)
{
	m_viewer = new SchematicSceneViewer(this);
	m_stageScene = new StageSchematicScene(this);
	m_fxScene = new FxSchematicScene(this);

	m_commonToolbar = new QToolBar(m_viewer);
	m_stageToolbar = new QToolBar(m_viewer);
	m_fxToolbar = new QToolBar(m_viewer);
	m_swapToolbar = new QToolBar(m_viewer);

	m_commonToolbar->setObjectName("ToolBarWithoutBorder");
	m_stageToolbar->setObjectName("ToolBarWithoutBorder");
	m_fxToolbar->setObjectName("ToolBarWithoutBorder");
	m_swapToolbar->setObjectName("ToolBarWithoutBorder");

	createToolbars();
	createActions();

	// layout
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->setMargin(1);
	mainLayout->setSpacing(0);
	{
		mainLayout->addWidget(m_viewer, 1);

		QFrame *bottomFrame = new QFrame(this);
		bottomFrame->setObjectName("SchematicBottomFrame");
		QHBoxLayout *horizontalLayout = new QHBoxLayout();
		horizontalLayout->setMargin(0);
		horizontalLayout->setSpacing(0);
		{
			horizontalLayout->addWidget(m_commonToolbar);
			horizontalLayout->addStretch();
			horizontalLayout->addWidget(m_fxToolbar);
			horizontalLayout->addWidget(m_stageToolbar);
			horizontalLayout->addWidget(m_swapToolbar);
		}
		bottomFrame->setLayout(horizontalLayout);

		mainLayout->addWidget(bottomFrame, 0);
	}
	setLayout(mainLayout);

	connect(m_fxScene, SIGNAL(showPreview(TFxP)), this, SIGNAL(showPreview(TFxP)));
	connect(m_fxScene, SIGNAL(doCollapse(const QList<TFxP> &)), this, SIGNAL(doCollapse(const QList<TFxP> &)));
	connect(m_stageScene, SIGNAL(doCollapse(QList<TStageObjectId>)), this, SIGNAL(doCollapse(QList<TStageObjectId>)));
	connect(m_fxScene, SIGNAL(doExplodeChild(const QList<TFxP> &)), this, SIGNAL(doExplodeChild(const QList<TFxP> &)));
	connect(m_stageScene, SIGNAL(doExplodeChild(QList<TStageObjectId>)), this, SIGNAL(doExplodeChild(QList<TStageObjectId>)));
	connect(m_stageScene, SIGNAL(editObject()), this, SIGNAL(editObject()));
	connect(m_fxScene, SIGNAL(editObject()), this, SIGNAL(editObject()));

	m_viewer->setScene(m_stageScene);
	m_fxToolbar->hide();

	setFocusProxy(m_viewer);
}