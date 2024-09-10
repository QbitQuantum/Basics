bool Module::event(QEvent *ev)
{
    if (ev->type() == ActionCreatedEvent::eventType()) {
        ActionCreatedEvent *event = static_cast<ActionCreatedEvent*>(ev);
        if (event->generator() == p->tagsGenerator.data()) {
            QAction *action = event->action();
            QMenu *menu = new QMenu(p->widget);
            QAction *act = menu->addAction(tr("Select tags"));
            connect(act, SIGNAL(triggered()), this, SLOT(onSelectTagsTriggered()));
            act = menu->addAction(tr("Reset"));
            connect(act, SIGNAL(triggered()), this, SLOT(onResetTagsTriggered()));
            action->setMenu(menu);
        }
    }
    return QObject::event(ev);
}