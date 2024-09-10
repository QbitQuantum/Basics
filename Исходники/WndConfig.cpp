//---------------------------------------------------------------------------
// setupControls
//---------------------------------------------------------------------------
void WndConfig::setupControls (void)
{
  AppSettings& settings = *App::instance()->settings();
  QHBoxLayout* pRootLayout = new QHBoxLayout;
  QVBoxLayout* pLeftLayout = new QVBoxLayout;

  // options
  {
    QVBoxLayout* pVBox;
    uint uiConfiguredLogStep   = settings.getLogStep();
    uint auiProposedLogSteps[] = { 1, 2, 3, 4, 5, 10, 20, 30, 60, 120, 180, 240, 300, 600, 1200, 1800, 3600, 7200, 10800 };
    int  iDefaultLogStepIdx    = 4; // 5 seconds

    pVBox = new QVBoxLayout;
    pVBox->setSpacing(1);

    m_pCboLogStep = new QMaemoComboBox(tr("Log step"), this);
    m_pCboLogStep->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    m_pCboLogStep->setTextAlignment(Qt::AlignLeft);

    for (int i = 0; i < sizeof(auiProposedLogSteps)/sizeof(auiProposedLogSteps[0]); ++i)
    {
      if (auiProposedLogSteps[i] >= AppSettings::logStepBounds().first ||
          auiProposedLogSteps[i] <= AppSettings::logStepBounds().second)
      {
        QString strItem;
        uint    uiBestAllowedFixStep = Location::selectBestAllowedFixStep(auiProposedLogSteps[i]);

        if (auiProposedLogSteps[i] < 60)
        {
          strItem.sprintf(
            "%u second%s (refresh : %us)",
            auiProposedLogSteps[i],
            (auiProposedLogSteps[i] == 1) ? "" : "s",
            uiBestAllowedFixStep);
        }
        else if (auiProposedLogSteps[i] < 3600)
        {
          uint uiMinutes = auiProposedLogSteps[i] / 60;

          strItem.sprintf(
            "%u minute%s (refresh : %us)",
            uiMinutes,
            (uiMinutes == 1) ? "" : "s",
            uiBestAllowedFixStep);
        }
        else
        {
          uint uiHours = auiProposedLogSteps[i] / 3600;

          strItem.sprintf(
            "%u hour%s (refresh : %us)",
            uiHours,
            (uiHours == 1) ? "" : "s",
            uiBestAllowedFixStep);
        }

        m_pCboLogStep->addItem(strItem, QVariant(auiProposedLogSteps[i]));
        if (auiProposedLogSteps[i] == uiConfiguredLogStep)
          iDefaultLogStepIdx = i;
      }
    }
    m_pCboLogStep->setCurrentIndex(iDefaultLogStepIdx);

    m_pChkGpsAssisted = new QCheckBox(tr("Assisted GPS"));
    m_pChkGpsAssisted->setCheckState(settings.getGpsAssisted() ? Qt::Checked : Qt::Unchecked);

    m_pChkGpsAlwaysConnected = new QCheckBox(tr("GPS always connected"));
    m_pChkGpsAlwaysConnected->setCheckState(settings.getGpsAlwaysConnected() ? Qt::Checked : Qt::Unchecked);

    m_pChkAlwaysCreateNewFile = new QCheckBox(tr("Always create new file (old behavior)"));
    m_pChkAlwaysCreateNewFile->setCheckState(settings.getAlwaysCreateNewFile() ? Qt::Checked : Qt::Unchecked);

    m_pChkAskPointName = new QCheckBox(tr("Ask for point name before snap"));
    m_pChkAskPointName->setCheckState(settings.getAskPointName() ? Qt::Checked : Qt::Unchecked);

    m_pChkAskPauseName = new QCheckBox(tr("Ask for a name when pausing"));
    m_pChkAskPauseName->setCheckState(settings.getAskPauseName() ? Qt::Checked : Qt::Unchecked);

    m_pCboUnitSystem = new QMaemoComboBox(tr("Unit system"), this);
    m_pCboUnitSystem->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    m_pCboUnitSystem->addItem(AppSettings::unitSystemToName(UNITSYSTEM_METRIC),    QVariant(UNITSYSTEM_METRIC));
    m_pCboUnitSystem->addItem(AppSettings::unitSystemToName(UNITSYSTEM_IMPERIAL),  QVariant(UNITSYSTEM_IMPERIAL));
    m_pCboUnitSystem->setCurrentIndex(settings.getUnitSystem());

    m_pCboHorizSpeedUnit = new QMaemoComboBox(tr("Horizontal speed unit"), this);
    m_pCboHorizSpeedUnit->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    m_pCboHorizSpeedUnit->addItem(AppSettings::horizSpeedUnitToName(HORIZSPEEDUNIT_KMH),   QVariant(HORIZSPEEDUNIT_KMH));
    m_pCboHorizSpeedUnit->addItem(AppSettings::horizSpeedUnitToName(HORIZSPEEDUNIT_MPH),   QVariant(HORIZSPEEDUNIT_MPH));
    m_pCboHorizSpeedUnit->addItem(AppSettings::horizSpeedUnitToName(HORIZSPEEDUNIT_MS),    QVariant(HORIZSPEEDUNIT_MS));
    m_pCboHorizSpeedUnit->addItem(AppSettings::horizSpeedUnitToName(HORIZSPEEDUNIT_KNOTS), QVariant(HORIZSPEEDUNIT_KNOTS));
    m_pCboHorizSpeedUnit->setCurrentIndex(settings.getHorizSpeedUnit());

    m_pChkPreventBlankScreen = new QCheckBox(tr("Prevent screen blanking"));
    m_pChkPreventBlankScreen->setCheckState(settings.getPreventBlankScreen() ? Qt::Checked : Qt::Unchecked);

    pVBox->addWidget(m_pCboLogStep);
    pVBox->addWidget(m_pChkGpsAssisted);
    pVBox->addWidget(m_pChkGpsAlwaysConnected);
    pVBox->addWidget(m_pChkAlwaysCreateNewFile);
    pVBox->addWidget(m_pChkAskPointName);
    pVBox->addWidget(m_pChkAskPauseName);
    pVBox->addWidget(m_pCboUnitSystem);
    pVBox->addWidget(m_pCboHorizSpeedUnit);
    pVBox->addWidget(m_pChkPreventBlankScreen);
    pLeftLayout->addLayout(pVBox);
  }

  // main layout setup
  {
    QScrollArea* pScrollArea = new QScrollArea;
    QWidget*     pScrollWidget = new QWidget;
    QPushButton* pBtnDone = new QPushButton(tr("Done"));

    this->connect(pBtnDone, SIGNAL(clicked()), SLOT(onClickedDone()));

    pLeftLayout->setSpacing(0);
    pScrollWidget->setLayout(pLeftLayout);

    pScrollArea->setWidgetResizable(true);
    pScrollArea->setWidget(pScrollWidget);
    pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pScrollArea->setProperty("FingerScrollable", true);

    pRootLayout->setSpacing(1);
    pRootLayout->addWidget(pScrollArea);
    pRootLayout->addWidget(pBtnDone, 0, Qt::AlignBottom);
  }

  // apply layout
  this->setLayout(pRootLayout);
}