QGraphicsWidget *DesignerActionManager::createFormEditorToolBar(QGraphicsItem *parent)
{
    QList<ActionInterface* > actions = Utils::filtered(designerActions(),
                                                       [](ActionInterface *action) {
            return action->type() ==  ActionInterface::FormEditorAction
                && action->action()->isVisible();
    });

    Utils::sort(actions, [](ActionInterface *l, ActionInterface *r) {
        return l->priority() > r->priority();
    });

    QGraphicsWidget *toolbar = new QGraphicsWidget(parent);

    auto layout = new QGraphicsLinearLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    toolbar->setLayout(layout);

    for (ActionInterface *action : actions) {
        auto button = new FormEditorToolButton(action->action(), toolbar);
        layout->addItem(button);
    }

    toolbar->resize(toolbar->preferredSize());

    layout->invalidate();
    layout->activate();

    toolbar->update();

    return toolbar;
}