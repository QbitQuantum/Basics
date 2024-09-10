QtGnuplotWindow::QtGnuplotWindow(int id, QtGnuplotEventHandler* eventHandler, QWidget* parent)
    : QMainWindow(parent)
{
    m_eventHandler = eventHandler;
    m_id = id;
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon(":/images/gnuplot"));

    // Register as the main event receiver if not already created
    if (m_eventHandler == 0)
        m_eventHandler = new QtGnuplotEventHandler(this,
                "qtgnuplot" + QString::number(QCoreApplication::applicationPid()));

    // Central widget
    m_widget = new QtGnuplotWidget(m_id, m_eventHandler, this);
    connect(m_widget, SIGNAL(statusTextChanged(const QString&)), this, SLOT(on_setStatusText(const QString&)));
    setCentralWidget(m_widget);

    // Bars
    m_toolBar = new QToolBar(this);
    addToolBar(m_toolBar);
    statusBar()->showMessage(tr("Qt frontend for gnuplot"));

    // Actions
    QAction* copyToClipboardAction = new QAction(QIcon(":/images/clipboard"   ), tr("Copy to clipboard"), this);
    QAction* printAction           = new QAction(QIcon(":/images/print"       ), tr("Print"            ), this);
    QAction* exportAction          = new QAction(QIcon(":/images/export"      ), tr("Export"           ), this);
    QAction* exportPdfAction       = new QAction(QIcon(":/images/exportPDF"   ), tr("Export to PDF"    ), this);
    QAction* exportEpsAction       = new QAction(QIcon(":/images/exportVector"), tr("Export to EPS"    ), this);
    QAction* exportSvgAction       = new QAction(QIcon(":/images/exportVector"), tr("Export to SVG"    ), this);
    QAction* exportPngAction       = new QAction(QIcon(":/images/exportRaster"), tr("Export to image"  ), this);
    QAction* settingsAction        = new QAction(QIcon(":/images/settings"    ), tr("Settings"         ), this);
    connect(copyToClipboardAction, SIGNAL(triggered()), m_widget, SLOT(copyToClipboard()));
    connect(printAction,           SIGNAL(triggered()), m_widget, SLOT(print()));
    connect(exportPdfAction,       SIGNAL(triggered()), m_widget, SLOT(exportToPdf()));
    connect(exportEpsAction,       SIGNAL(triggered()), m_widget, SLOT(exportToEps()));
    connect(exportSvgAction,       SIGNAL(triggered()), m_widget, SLOT(exportToSvg()));
    connect(exportPngAction,       SIGNAL(triggered()), m_widget, SLOT(exportToImage()));
    connect(settingsAction,        SIGNAL(triggered()), m_widget, SLOT(showSettingsDialog()));
    QMenu* exportMenu = new QMenu(this);
    exportMenu->addAction(copyToClipboardAction);
    exportMenu->addAction(printAction);
    exportMenu->addAction(exportPdfAction);
//	exportMenu->addAction(exportEpsAction);
    exportMenu->addAction(exportSvgAction);
    exportMenu->addAction(exportPngAction);
    exportAction->setMenu(exportMenu);
    m_toolBar->addAction(exportAction);
    createAction(tr("Replot")       , 'e', ":/images/replot");
    createAction(tr("Show grid")    , 'g', ":/images/grid");
    createAction(tr("Previous zoom"), 'p', ":/images/zoomPrevious");
    createAction(tr("Next zoom")    , 'n', ":/images/zoomNext");
    createAction(tr("Autoscale")    , 'a', ":/images/autoscale");
    m_toolBar->addAction(settingsAction);
}