void KUrlNavigatorPlacesSelector::updateTeardownAction()
{
    const int rowCount = m_placesModel->rowCount();
    if (m_placesMenu->actions().size() == rowCount + 2) {
        // remove teardown action
        QAction *action = m_placesMenu->actions().at(rowCount + 1);
        m_placesMenu->removeAction(action);
        delete action;

        // remove separator
        action = m_placesMenu->actions().at(rowCount);
        m_placesMenu->removeAction(action);
        delete action;
    }

    const QModelIndex index = m_placesModel->index(m_selectedItem, 0);
    QAction *teardown = m_placesModel->teardownActionForIndex(index);
    if (teardown != 0) {
        teardown->setParent(m_placesMenu);
        teardown->setData("teardownAction");

        m_placesMenu->addSeparator();
        m_placesMenu->addAction(teardown);
    }
}