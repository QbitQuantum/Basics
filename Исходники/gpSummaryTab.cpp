// gpSummaryTab
bool gpSummaryTab::Init(gpTraceDataContainer* pDataContainer, gpTraceView* pSessionView, quint64 timelineStart, quint64 timelineEnd)
{
    m_pTraceView = pSessionView;
    m_pSessionDataContainer = pDataContainer;
    if (m_callType == API_CALL)
    {
        m_pSummaryTable = new gpCPUTraceSummaryTable(pDataContainer, pSessionView, m_timelineAbsoluteStart);
    }
    else if (m_callType == GPU_CALL)
    {
        m_pSummaryTable = new gpGPUTraceSummaryTable(pDataContainer, pSessionView, m_timelineAbsoluteStart);
    }
    else
    {
        m_pSummaryTable = new gpCommandListSummaryTable(pDataContainer, pSessionView, m_timelineAbsoluteStart);
    }
    bool rc = m_pSummaryTable->Init();
    if (rc == true)
    {
        m_pTop20Table = new acListCtrl(this);

        m_pTop20Caption = new QLabel(this);

        QHBoxLayout* pHLayout = new QHBoxLayout;
        QVBoxLayout* pLeftVLayout = new QVBoxLayout;
        QHBoxLayout* pLeftHLayout = new QHBoxLayout;
        QVBoxLayout* pRightVLayout = new QVBoxLayout;
        QSplitter* pVMainSplitter = new QSplitter(Qt::Horizontal);

        // set the margins to all layout to zero
        pHLayout->setContentsMargins(0, 0, 0, 0);
        pLeftVLayout->setContentsMargins(0, 0, 0, 0);
        pLeftHLayout->setContentsMargins(0, 0, 0, 0);
        pRightVLayout->setContentsMargins(0, 0, 0, 0);

        QWidget* pWidgetLeft = new QWidget;
        QWidget* pWidgetRight = new QWidget;

        m_pChkboxUseScope = new QCheckBox(GPU_STR_Use_Scope_Summary);

        QString styleSheetStr = QString("QDialog{border:1px solid gray;}");
        pLeftHLayout->addWidget(m_pChkboxUseScope, 0, Qt::AlignHCenter);
        pLeftVLayout->addLayout(pLeftHLayout);
        pWidgetLeft->setLayout(pLeftVLayout);
        pWidgetLeft->setStyleSheet(styleSheetStr);

        m_pSummaryTable->resizeColumnsToContents();
        pLeftVLayout->addWidget(m_pSummaryTable);
        m_pSummaryTable->SetSelectionBackgroundColor(acQAMD_CYAN_SELECTION_BKG_COLOUR);

        pLeftVLayout->setSpacing(0);
        pLeftVLayout->setMargin(1);

        QFont qFont = m_pTop20Caption->font();
        qFont.setBold(true);
        qFont.setPointSize(10);
        m_pTop20Caption->setFont(qFont);

        pRightVLayout->addWidget(m_pTop20Caption);
        QStringList columnCaptions;
        columnCaptions << "#";

        if (m_callType == API_CALL)
        {
            columnCaptions << GP_STR_SummaryTop20TableColumnThreadId;
        }

        columnCaptions << GP_STR_SummaryTop20TableColumnCallIndex;
        columnCaptions << GP_STR_SummaryTop20TableColumnTime;
        m_pTop20Table->initHeaders(columnCaptions, false);
        m_pTop20Table->setContextMenuPolicy(Qt::NoContextMenu);
        m_pTop20Table->resizeColumnsToContents();
        m_pTop20Table->setShowGrid(true);
        pRightVLayout->addWidget(m_pTop20Table);
        pRightVLayout->setSpacing(1);
        pRightVLayout->setMargin(1);
        pWidgetRight->setLayout(pRightVLayout);
        pWidgetRight->setStyleSheet(styleSheetStr);


        pVMainSplitter->addWidget(pWidgetLeft);
        pVMainSplitter->addWidget(pWidgetRight);

        int widgetWidth = geometry().right() - geometry().left();
        QList<int> sizes;
        sizes << (int)(widgetWidth * 0.75);
        sizes << (int)(widgetWidth * 0.25);
        pVMainSplitter->setSizes(sizes);
        pHLayout->addWidget(pVMainSplitter);

        setLayout(pHLayout);

        SetTimelineScope(false, timelineStart, timelineEnd);

        rc = connect(m_pChkboxUseScope, SIGNAL(toggled(bool)), this, SLOT(OnUseTimelineSelectionScopeChanged(bool)));
        GT_ASSERT(rc);
        rc = connect(m_pSummaryTable, SIGNAL(itemSelectionChanged()), this, SLOT(OnSummaryTableSelectionChanged()));
        GT_ASSERT(rc);
        rc = connect(m_pSummaryTable, SIGNAL(cellClicked(int, int)), this, SLOT(OnSummaryTableCellClicked(int, int)));
        GT_ASSERT(rc);
        rc = connect(m_pSummaryTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(OnSummaryTableCellDoubleClicked(int, int)));
        GT_ASSERT(rc);
        rc = connect(m_pTop20Table, SIGNAL(cellClicked(int, int)), this, SLOT(OnTop20TableCellClicked(int, int)));
        GT_ASSERT(rc);
        rc = connect(m_pTop20Table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(OnTop20TableCellDoubleClicked(int, int)));
        GT_ASSERT(rc);

        m_pSummaryTable->selectRow(0);
        OnSummaryTableSelectionChanged(); // NZ for some reason the signal isn't enough
    }