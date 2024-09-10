void ConsoleChannel::initCapabilityMenu(const QLCChannel* ch)
{
    QLCCapability* cap;
    QMenu* valueMenu;
    QAction* action;
    QString s;
    QString t;

    QListIterator <QLCCapability*> it(ch->capabilities());
    while (it.hasNext() == true)
    {
        cap = it.next();

        // Set the value range and name as the menu item's name
        s = QString("%1: %2 - %3").arg(cap->name())
            .arg(cap->min()).arg(cap->max());

        if (cap->max() - cap->min() > 0)
        {
            // Create submenu for ranges of more than one value
            valueMenu = new QMenu(m_menu);
            valueMenu->setTitle(s);

            /* Add a color icon */
            if (ch->group() == QLCChannel::Colour)
                valueMenu->setIcon(colorIcon(cap->name()));

            for (int i = cap->min(); i <= cap->max(); i++)
            {
                action = valueMenu->addAction(
                             t.sprintf("%.3d", i));
                action->setData(i);
            }

            m_menu->addMenu(valueMenu);
        }
        else
        {
            // Just one value in this range, put that into the menu
            action = m_menu->addAction(s);
            action->setData(cap->min());

            /* Add a color icon */
            if (ch->group() == QLCChannel::Colour)
                action->setIcon(colorIcon(cap->name()));
        }
    }

    // Connect menu item activation signal to this
    connect(m_menu, SIGNAL(triggered(QAction*)),
            this, SLOT(slotContextMenuTriggered(QAction*)));

    // Set the menu also as the preset button's popup menu
    m_presetButton->setMenu(m_menu);
}