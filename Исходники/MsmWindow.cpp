MsmWindow::MsmWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Prepare the view area
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    QQuickView *view = new QQuickView();
    menuView = QWidget::createWindowContainer(view, this);
    menuView->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl("qrc:/qml/main.qml"));
    stackedWidget->addWidget(menuView);
    stackedWidget->setCurrentWidget(menuView);

    moduleView = new ModuleView();
    stackedWidget->addWidget(moduleView);

    QQuickItem *rootObject = view->rootObject();
    QQuickItem::connect(rootObject, SIGNAL(itemClicked(QString)),
                     this, SLOT(loadModule(QString)));

    ModuleView::connect(moduleView, &ModuleView::closeRequest,
                        [=]() {
        moduleView->resolveChanges();
        moduleView->closeModules();
        stackedWidget->setCurrentWidget(menuView);
    });

    init();
    readPositionSettings();
}