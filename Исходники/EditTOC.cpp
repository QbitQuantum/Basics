void EditTOC::ConnectSignalsToSlots()
{
    connect(this,               SIGNAL(accepted()),           this, SLOT(Save()));
    connect(ui.AddEntryAbove,   SIGNAL(clicked()),            this, SLOT(AddEntryAbove()));
    connect(ui.AddEntryBelow,   SIGNAL(clicked()),            this, SLOT(AddEntryBelow()));
    connect(ui.DeleteEntry,     SIGNAL(clicked()),            this, SLOT(DeleteEntry()));
    connect(ui.MoveLeft,        SIGNAL(clicked()),            this, SLOT(MoveLeft()));
    connect(ui.MoveRight,       SIGNAL(clicked()),            this, SLOT(MoveRight()));
    connect(ui.MoveUp,          SIGNAL(clicked()),            this, SLOT(MoveUp()));
    connect(ui.MoveDown,        SIGNAL(clicked()),            this, SLOT(MoveDown()));
    connect(m_MoveUp,           SIGNAL(triggered()),          this, SLOT(MoveUp()));
    connect(m_MoveDown,         SIGNAL(triggered()),          this, SLOT(MoveDown()));
    connect(ui.SelectTarget,    SIGNAL(clicked()),            this, SLOT(SelectTarget()));
    connect(ui.TOCTree,         SIGNAL(customContextMenuRequested(const QPoint &)),
            this,               SLOT(OpenContextMenu(const QPoint &)));
    connect(m_Rename,           SIGNAL(triggered()), this, SLOT(Rename()));
    connect(m_Delete,           SIGNAL(triggered()), this, SLOT(DeleteEntry()));
    connect(m_CollapseAll,      SIGNAL(triggered()), this, SLOT(CollapseAll()));
    connect(m_ExpandAll,        SIGNAL(triggered()), this, SLOT(ExpandAll()));
}