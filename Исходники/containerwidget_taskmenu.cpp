ContainerWidgetTaskMenu::ContainerWidgetTaskMenu(QWidget *widget, ContainerType type, QObject *parent) :
    QDesignerTaskMenu(widget, parent),
    m_type(type),
    m_containerWidget(widget),
    m_core(formWindow()->core()),
    m_pagePromotionTaskMenu(new PromotionTaskMenu(0, PromotionTaskMenu::ModeSingleWidget, this)),
    m_pageMenuAction(new QAction(this)),
    m_pageMenu(new QMenu),
    m_actionInsertPageAfter(new QAction(this)),
    m_actionInsertPage(0),
    m_actionDeletePage(new QAction(tr("Delete"), this))
{
    Q_ASSERT(m_core);
    m_taskActions.append(createSeparator());

    connect(m_actionDeletePage, SIGNAL(triggered()), this, SLOT(removeCurrentPage()));

    connect(m_actionInsertPageAfter, SIGNAL(triggered()), this, SLOT(addPageAfter()));
    // Empty Per-Page submenu, deletion and promotion. Updated on demand due to promotion state
    switch (m_type) {
    case WizardContainer:
    case PageContainer:
        m_taskActions.append(createSeparator()); // for the browse actions
        break;
    case MdiContainer:
        break;
    }
    // submenu
    m_pageMenuAction->setMenu(m_pageMenu);
    m_taskActions.append(m_pageMenuAction);
    // Insertion
    switch (m_type) {
    case WizardContainer:
    case PageContainer: { // Before and after in a submenu
        QAction *insertMenuAction = new QAction(tr("Insert"), this);
        QMenu *insertMenu = new QMenu;
        // before
        m_actionInsertPage = new QAction(tr("Insert Page Before Current Page"), this);
        connect(m_actionInsertPage, SIGNAL(triggered()), this, SLOT(addPage()));
        insertMenu->addAction(m_actionInsertPage);
        // after
        m_actionInsertPageAfter->setText(tr("Insert Page After Current Page"));
        insertMenu->addAction(m_actionInsertPageAfter);

        insertMenuAction->setMenu(insertMenu);
        m_taskActions.append(insertMenuAction);
    }
        break;
    case MdiContainer: // No concept of order
        m_actionInsertPageAfter->setText(tr("Add Subwindow"));
        m_taskActions.append(m_actionInsertPageAfter);
        break;
    }
}