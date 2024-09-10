PromotionTaskMenu::PromotionState  PromotionTaskMenu::createPromotionActions(QDesignerFormWindowInterface *formWindow)
{
    // clear out old
    if (!m_promotionActions.empty()) {
        qDeleteAll(m_promotionActions);
        m_promotionActions.clear();
    }
    // No promotion of main container
    if (formWindow->mainContainer() == m_widget)
        return NotApplicable;

    // Check for a homogenous selection
    const PromotionSelectionList promotionSelection = promotionSelectionList(formWindow);

    if (promotionSelection.empty())
        return NoHomogenousSelection;

    QDesignerFormEditorInterface *core = formWindow->core();
    // if it is promoted: demote only.
    if (isPromoted(formWindow->core(), m_widget)) {
        const QString label = m_demoteLabel.arg( promotedExtends(core , m_widget));
        QAction *demoteAction = new QAction(label, this);
        connect(demoteAction, SIGNAL(triggered()), this, SLOT(slotDemoteFromCustomWidget()));
        m_promotionActions.push_back(demoteAction);
        return CanDemote;
    }
    // figure out candidates
    const QString baseClassName = WidgetFactory::classNameOf(core,  m_widget);
    const WidgetDataBaseItemList candidates = promotionCandidates(core->widgetDataBase(), baseClassName );
    if (candidates.empty()) {
        // Is this thing promotable at all?
        return QDesignerPromotionDialog::baseClassNames(core->promotion()).contains(baseClassName) ?  CanPromote : NotApplicable;
    }
    // Set up a signal mapper to associate class names
    if (!m_promotionMapper) {
        m_promotionMapper = new QSignalMapper(this);
        connect(m_promotionMapper, SIGNAL(mapped(QString)), this, SLOT(slotPromoteToCustomWidget(QString)));
    }

    QMenu *candidatesMenu = new QMenu();
    // Create a sub menu
    const WidgetDataBaseItemList::const_iterator cend = candidates.constEnd();
    // Set up actions and map class names
    for (WidgetDataBaseItemList::const_iterator it = candidates.constBegin(); it != cend; ++it) {
        const QString customClassName = (*it)->name();
        QAction *action = new QAction((*it)->name(), this);
        connect(action, SIGNAL(triggered()), m_promotionMapper, SLOT(map()));
        m_promotionMapper->setMapping(action, customClassName);
        candidatesMenu->addAction(action);
    }
    // Sub menu action
    QAction *subMenuAction = new QAction(m_promoteLabel, this);
    subMenuAction->setMenu(candidatesMenu);
    m_promotionActions.push_back(subMenuAction);
    return CanPromote;
}