//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void AboutDialog::create()
{
    // Only allowed to call once
    assert(!m_isCreated);

    // Only show app info if app name is non-empty
    bool showAppInfo = !m_appName.isEmpty();

    // Do an initial resize, dialog will resize itself later based on the widgets we have added
    resize(10, 10); 


    // Set caption, different text depending on whether we're showing app info or not
    QString dlgCaption = "Version Information Details";
    if (showAppInfo)
    {
        dlgCaption = "About " + m_appName;
        if (m_isDebugBuild) dlgCaption += " (DEBUG)";
    }

    setWindowTitle(dlgCaption);


    // Create the dialog's main layout
    QVBoxLayout* dlgMainLayout = new QVBoxLayout(this); 

    // The the top layout
    QVBoxLayout* topLayout = new QVBoxLayout; 
    topLayout->setSpacing(3);


    // Possibly create and set text for widgets with app info
    if (showAppInfo)
    {
        QVBoxLayout* appInfoLayout = new QVBoxLayout; 
        appInfoLayout->setSpacing(3);

        // Always do app name
        assert(!m_appName.isEmpty());
        QLabel* appNameLabel = new QLabel(this);

        QFont appNameFont(appNameLabel->font());
        appNameFont.setPointSize(14);
        appNameFont.setBold(true);
        appNameLabel->setFont(appNameFont); 
        appNameLabel->setText(m_appName);
        appInfoLayout->addWidget(appNameLabel);

        // Application version if specified
        if (!m_appVersion.isEmpty())
        {
            QString appVer = m_appVersion;
//			appVer += cvf::System::is64Bit() ? "  (64-bit)" : "  (32-bit)";

            QLabel* appVersionLabel = new QLabel(this);
            QFont appVersionFont(appVersionLabel->font());
            appVersionFont.setPointSize(8);
            appVersionFont.setBold(TRUE);
            appVersionLabel->setFont(appVersionFont); 
            appVersionLabel->setText(appVer);
            appInfoLayout->addWidget(appVersionLabel);
        }

        // Application copyright if specified
        if (!m_appCopyright.isEmpty())
        {
            QLabel* appCopyrightLabel = new QLabel(this);
            QFont appCopyrightFont(appCopyrightLabel->font());
            appCopyrightFont.setPointSize(8);
            appCopyrightFont.setBold(TRUE);
            appCopyrightLabel->setFont(appCopyrightFont); 
            appCopyrightLabel->setText(m_appCopyright);
            appInfoLayout->addWidget(appCopyrightLabel);
        }

        QFrame* line = new QFrame(this);
        line->setProperty("frameShape", (int)QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setFrameShape(QFrame::HLine);
        appInfoLayout->addWidget(line);

        topLayout->addLayout(appInfoLayout);
    }


    // Possibly show extend version info
    if (m_showQtVersion	    ||
        m_verLabels.size() > 0)
    {
        QGridLayout* verInfoLayout = new QGridLayout; 
        verInfoLayout->setSpacing(0);

        int insertRow = 0;

        // Qt version
        if (m_showQtVersion)
        {
            addStringPairToVerInfoLayout("Qt ver.:  ", qVersion(), verInfoLayout, insertRow++);
        }

        // Custom specified labels
        if (m_verLabels.size() > 0)
        {
            assert(m_verLabels.size() == m_verTexts.size());

            int i;
            for (i = 0; i < m_verLabels.size(); i++)
            {
                addStringPairToVerInfoLayout(m_verLabels[i], m_verTexts[i], verInfoLayout, insertRow++);
            }
        }

        topLayout->addLayout(verInfoLayout);
    }


    dlgMainLayout->addLayout(topLayout);

    QSpacerItem* spacer1 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    dlgMainLayout->addItem(spacer1);


    // The bottom part with the OK button and
    // possibly text label indicating that we're running a debug build
    QHBoxLayout* bottomLayout = new QHBoxLayout;

    // Indicate that this is a debug build
    if (m_isDebugBuild)
    {
        QLabel* debugLabel = new QLabel(this);
        debugLabel->setText("<font color='brown'><b>This is a DEBUG build...</b></font>");
        bottomLayout->addWidget(debugLabel);
    }


    // Add OK button
    QSpacerItem* spacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    bottomLayout->addItem(spacer2);

    QPushButton* buttonOk = new QPushButton("&OK", this);
    buttonOk->setAutoDefault(TRUE);
    buttonOk->setDefault(TRUE);
    buttonOk->setFocus();
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()) );
    bottomLayout->addWidget(buttonOk);

    dlgMainLayout->addLayout(bottomLayout);

    m_isCreated = true;
}