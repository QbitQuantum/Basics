EFFEditorInspectorPanel::EFFEditorInspectorPanel(QWidget * parent) : QDockWidget(parent)
{
	/*m_pTitleBar = new EFFEditorUIDockWidgetTitleBar(this, tr("Inspector"));
	setWindowTitle(tr("Inspector"));
	setTitleBarWidget(m_pTitleBar);

	QObject::connect(this, SIGNAL(visibilityChanged(bool)), this, SLOT(titleBarAddOrDeleteTab(bool)));*/

	setWindowTitle(tr("Inspector"));
	setObjectName(tr("InspectorPanel"));
	setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);

	m_pContent = new QWidget(this);

	m_pMainLayout = new QVBoxLayout();
	m_pMainLayout->setContentsMargins(2, 1, 1, 1);
	m_pMainLayout->setSpacing(0);


	QWidget * inspectorHeadPanel = new QWidget();
	inspectorHeadPanel->setObjectName("inspectorHead");

	QVBoxLayout * inspectorHeadLayout = new QVBoxLayout();
	inspectorHeadLayout->setContentsMargins(3, 3, 3, 3);
	inspectorHeadLayout->setSpacing(3);

	QHBoxLayout * nameLayout = new QHBoxLayout();
	QCheckBox * nameCheckBox = new QCheckBox();
	nameLayout->addWidget(nameCheckBox);
	m_pNameEdit = new QLineEdit();
	nameLayout->addWidget(m_pNameEdit);
	QCheckBox * staticCheckBox = new QCheckBox();
	nameLayout->addWidget(staticCheckBox);
	QPushButton * staticButton = new QPushButton();
	nameLayout->addWidget(staticButton);
	QPushButton * staticTypeSelectButton = new QPushButton();
	nameLayout->addWidget(staticTypeSelectButton);

	inspectorHeadLayout->addLayout(nameLayout);


	QHBoxLayout * tagAndLayerLayout = new QHBoxLayout();
	QLabel * tagLabel = new QLabel();
	tagLabel->setText(tr("Tag"));
	tagAndLayerLayout->addWidget(tagLabel);
	QPushButton * tagButton = new QPushButton();
	tagAndLayerLayout->addWidget(tagButton, 1);

	QLabel * layerLabel = new QLabel();
	layerLabel->setText(tr("Layer"));
	tagAndLayerLayout->addWidget(layerLabel);
	QPushButton * layerButton = new QPushButton();
	tagAndLayerLayout->addWidget(layerButton, 1);

	inspectorHeadLayout->addLayout(tagAndLayerLayout);
	inspectorHeadPanel->setLayout(inspectorHeadLayout);

	m_pMainLayout->addWidget(inspectorHeadPanel);

	m_pTransformPanel = new EFFEditorTransformPanel();
	m_pMainLayout->addWidget(m_pTransformPanel);

	//Ìî³äÊ£ÓàÇøÓò
	QWidget * pWidget = new QWidget();
	m_pMainLayout->addWidget(pWidget, 1);


	m_pContent->setLayout(m_pMainLayout);
	setWidget(m_pContent);
}