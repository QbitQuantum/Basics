void FlowTab::ConnectBookViewSignalsToSlots()
{
    connect(m_wBookView, SIGNAL(ZoomFactorChanged(float)), this, SIGNAL(ZoomFactorChanged(float)));
    connect(m_wBookView, SIGNAL(selectionChanged()), this, SIGNAL(SelectionChanged()));
    connect(m_wBookView, SIGNAL(FocusLost(QWidget *)), this, SLOT(LeaveEditor(QWidget *)));
    connect(m_wBookView, SIGNAL(InsertFile()), this, SIGNAL(InsertFileRequest()));
    connect(m_wBookView, SIGNAL(LinkClicked(const QUrl &)), this, SIGNAL(LinkClicked(const QUrl &)));
    connect(m_wBookView, SIGNAL(ClipboardSaveRequest()),    this, SIGNAL(ClipboardSaveRequest()));
    connect(m_wBookView, SIGNAL(ClipboardRestoreRequest()), this, SIGNAL(ClipboardRestoreRequest()));
    connect(m_wBookView, SIGNAL(InsertedFileOpenedExternally(const QString &)), this, SIGNAL(InsertedFileOpenedExternally(const QString &)));
    connect(m_wBookView, SIGNAL(InsertedFileSaveAs(const QUrl &)), this, SIGNAL(InsertedFileSaveAs(const QUrl &)));
    connect(m_wBookView, SIGNAL(ShowStatusMessageRequest(const QString &)), this, SIGNAL(ShowStatusMessageRequest(const QString &)));
    connect(m_wBookView, SIGNAL(OpenClipEditorRequest(ClipEditorModel::clipEntry *)), this, SIGNAL(OpenClipEditorRequest(ClipEditorModel::clipEntry *)));
    connect(m_wBookView, SIGNAL(OpenIndexEditorRequest(IndexEditorModel::indexEntry *)), this, SIGNAL(OpenIndexEditorRequest(IndexEditorModel::indexEntry *)));
    connect(m_wBookView, SIGNAL(textChanged()), this, SLOT(EmitContentChanged()));
    connect(m_wBookView, SIGNAL(InspectElement()), this, SIGNAL(InspectElement()));
    connect(m_wBookView, SIGNAL(PageUpdated()), this, SLOT(EmitUpdatePreview()));
    connect(m_wBookView, SIGNAL(PageClicked()), this, SLOT(EmitUpdatePreviewImmediately()));
    connect(m_wBookView, SIGNAL(PageOpened()), this, SLOT(EmitUpdatePreviewImmediately()));
    connect(m_wBookView, SIGNAL(DocumentLoaded()), this, SLOT(EmitUpdatePreviewImmediately()));
}