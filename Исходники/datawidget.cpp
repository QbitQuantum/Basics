DataWidget::DataWidget(DataDescription *dataDescription,
                       WidgetWindowsManager *widgetWindowsManager,
                       MainWindow *mainWindow,
                       bool inside) :
AbstractWidgetWindow(widgetWindowsManager, mainWindow, inside)
{
    _dataDescription = dataDescription;
    _internalWidget = 0;
    // For the plot widget
    _curve = 0;
    _curveData = 0;

    _dataWidgetNames = _mainWindow->dataWidgetNames();
    _dataWidgetPossibilities = _mainWindow->dataWidgetPossibilities() ->value(
            _dataDescription->type).values();

    // Init context menu actions
    QActionGroup *actionGroup = new QActionGroup(this);
    for (int i = 0; i < _dataWidgetPossibilities.count(); i++)
    {
        QAction *action = new QAction(
                _dataWidgetNames ->value(_dataWidgetPossibilities.at(i)),
                actionGroup);
        action->setCheckable(true);
        if (_dataWidgetPossibilities.at(i) == _dataDescription->widget)
        {
            action->setChecked(true);
        }
        QObject::connect(action, SIGNAL(triggered()), this,
                         SLOT(widgetTypeChanged()));
        actionGroup->addAction(action);
    }
    addActions(actionGroup->actions());

    // Set attributes
    setContextMenuPolicy(Qt::ActionsContextMenu);

    // Init GUI
    setWindowTitle(_dataDescription->descriptionString);
    setWindowIcon(QIcon(":/images/widget.png"));
    // Set layout
    QVBoxLayout *globalLayout = new QVBoxLayout();
    setLayout(globalLayout);
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(_inOutButton);
    QString labelText = _dataDescription->descriptionString;
    if (_dataDescription->descriptionString.size() > 14)
    {
        labelText.truncate(12);
        labelText.append("...");
    }
    QLabel *dataTitle = new QLabel(labelText);
    dataTitle->setToolTip(_dataDescription->descriptionString);
    topLayout->addWidget(dataTitle, 0, Qt::AlignHCenter);
    dataTitle->setFixedHeight(dataTitle->sizeHint().height());
    globalLayout->addLayout(topLayout);

    // Create internal widget
    createInternalWidget();

    setParent(0); // Needed if it is a flying window
    // Will be updated anyway if it goes into the MDI area
    // However the object HAS to be constructed with the main window as parent
    // so it can connect to its slots.

    // Setup automatic cleanup
    QObject::connect(this, SIGNAL(destroyed()), _mainWindow,
                     SLOT(removeDestroyedDataWidgets()));

    qDebug() << "DataWidget : initializing [desc"
            << _dataDescription->descriptionString << "; id"
            << _dataDescription->id << "; type" << _dataDescription->type
            << "; min" << _dataDescription->valMin << "; max"
            << _dataDescription->valMax << "; widget"
            << _dataDescription->widget << "]";
}