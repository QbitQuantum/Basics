BackgroundWidget::BackgroundWidget(QWidget *parent) :
    QWidget(parent)
{

    this->setWindowTitle("Background");
    this->setWindowIcon(QIcon(":/resources/icons/resources/background.png"));

    zoomInAction = new QAction(QIcon(":/icons/actions/zoom-in.png"), "Zoom In", NULL);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
    zoomOutAction = new QAction(QIcon(":/icons/actions/zoom-out.png"), "Zoom Out", NULL);
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));
    QAction* openAction = new QAction(QIcon(":/icons/actions/open.png"), "Load from file", NULL);
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    QAction* saveAction = new QAction(QIcon(":/icons/actions/save.png"), "Save to file", NULL);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    QAction* printAction = new QAction(QIcon(":/icons/actions/print.png"), "Print", NULL);
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    QVBoxLayout* propertiesLayout = new QVBoxLayout();

    QLabel* nameLabel = new QLabel("Name: ");
    QLineEdit* nameEdit = new QLineEdit("bg_0", this);

    QToolBar* toolBar = new QToolBar();
    toolBar->addAction(QIcon(":/icons/actions/accept.png"), "Save Changes");
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(printAction);

    toolBar->addSeparator();
    toolBar->addAction(zoomInAction);
    toolBar->addAction(zoomOutAction);
    toolBar->addSeparator();
    toolBar->addWidget(nameLabel);
    toolBar->addWidget(nameEdit);

    toolBar->setStyleSheet(" QToolBar { height: 18px; width: 18px; icon-size: 18px; } ");

    QCheckBox* smoothCheckBox = new QCheckBox("Smooth", this);
    QCheckBox* transparentCheckBox = new QCheckBox("Transparent", this);
    QCheckBox* preloadCheckBox = new QCheckBox("Preload", this);
    QCheckBox* tilesetCheckBox = new QCheckBox("Tileset", this);

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);


    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    propertiesLayout->addWidget(smoothCheckBox);
    propertiesLayout->addWidget(transparentCheckBox);
    propertiesLayout->addWidget(preloadCheckBox);
    propertiesLayout->addWidget(tilesetCheckBox);
    QSplitter* horizontalSplitter = new QSplitter(this);
    QWidget* propertiesWidget = new QWidget(this, Qt::WindowTitleHint);
    QFormLayout* propertiesFormLayout = new QFormLayout();
    propertiesFormLayout->setLayout(0, QFormLayout::SpanningRole, propertiesLayout);
    propertiesWidget->setLayout(propertiesFormLayout);

    horizontalSplitter->addWidget(propertiesWidget);
    horizontalSplitter->addWidget(scrollArea);
    horizontalSplitter->setStretchFactor(0, 0);
    horizontalSplitter->setStretchFactor(1, 1);

    QVBoxLayout* verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(toolBar);
    verticalLayout->addWidget(horizontalSplitter);
    QStatusBar* statusBar = new QStatusBar();
    statusBar->showMessage("Width: 0 | Height: 0 | Memory: 0 B | Zoom: 100%");
    statusBar->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    verticalLayout->addWidget(statusBar);
    verticalLayout->setContentsMargins(2, 2, 2, 2);
    this->setLayout(verticalLayout);
}