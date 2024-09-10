ConfigManager::ConfigManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigManager)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window |
                   Qt::WindowTitleHint |
                   Qt::WindowCloseButtonHint |
                   Qt::WindowStaysOnTopHint);

    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    size(),
                                    qApp->desktop()->availableGeometry()));

    #ifdef Q_OS_MAC
    this->setWindowIcon(QIcon(":/cat_builder.icns"));
    ui->frame->setAutoFillBackground(false);
    ui->frame->setFrameShape(QFrame::NoFrame);
    ui->frame->setLineWidth(0);
    #endif
    #ifdef Q_OS_WIN
    this->setWindowIcon(QIcon(":/cat_builder.ico"));

    if(QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA)
    {
        if(QtWin::isCompositionEnabled())
        {
            this->setAttribute(Qt::WA_TranslucentBackground, true);
            QtWin::extendFrameIntoClientArea(this, -1, -1, -1, 1);
            QtWin::enableBlurBehindWindow(this);
        }
        else
        {
            QtWin::resetExtendedFrame(this);
            setAttribute(Qt::WA_TranslucentBackground, false);
        }
    }
    #endif

    connect(ui->configList, SIGNAL(clicked(QModelIndex)), ui->configList, SLOT(update()));
    connect(this, SIGNAL(accepted()), this, SLOT(saveCurrentSettings()));

    m_currentConfig = "";
    m_themePackName = "";
    m_doAskAgain    = false;
    loadConfigPackList();
}