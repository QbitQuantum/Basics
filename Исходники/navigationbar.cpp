void NavigationBar::reloadLayout()
{
    if (m_widgets.isEmpty()) {
        return;
    }

    setUpdatesEnabled(false);

    // Clear layout
    while (m_layout->count() != 0) {
        QLayoutItem *item = m_layout->takeAt(0);
        if (!item) {
            continue;
        }
        QWidget *widget = item->widget();
        if (!widget) {
            continue;
        }
        widget->setParent(nullptr);
    }

    // Hide all widgets
    for (const WidgetData &data : m_widgets) {
        data.widget->hide();
    }

    // Add widgets to layout
    for (const QString &id : qAsConst(m_layoutIds)) {
        const WidgetData data = m_widgets.value(id);
        if (data.widget) {
            m_layout->addWidget(data.widget);
            NavigationBarToolButton *button = qobject_cast<NavigationBarToolButton*>(data.widget);
            if (button) {
                button->updateVisibility();
            } else {
                data.widget->show();
            }
        }
    }

    m_layout->addWidget(m_supMenu);

    // Make sure search bar is visible
    if (m_searchLine->isVisible() && m_navigationSplitter->sizes().at(1) == 0) {
        const int locationBarSize = m_navigationSplitter->sizes().at(0);
        setSplitterSizes(locationBarSize - 50, 50);
    }

    if (m_window->isFullScreen()) {
        enterFullScreen();
    } else {
        leaveFullScreen();
    }

    setUpdatesEnabled(true);
}