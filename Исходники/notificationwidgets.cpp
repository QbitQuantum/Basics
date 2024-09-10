NotificationActionsButtonsWidget::NotificationActionsButtonsWidget(const QStringList& actions, QWidget *parent)
    : NotificationActionsWidget(actions, parent)
{
    QHashIterator<QString,QString> it(m_actionMap);
    QHBoxLayout *l = new QHBoxLayout();
    setLayout(l);

    QButtonGroup *group = new QButtonGroup(this);

    while (it.hasNext())
    {
        it.next();
        QPushButton *b = new QPushButton(it.value(), this);
        l->addWidget(b);
        group->addButton(b);
        if (it.key() == "default")
        {
            b->setFocus(Qt::OtherFocusReason);
            m_defaultAction = it.key();
        }
    }
    connect(group, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(actionButtonActivated(QAbstractButton*)));
}