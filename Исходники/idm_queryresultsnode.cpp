void QueryResultsNode::create(const QModelIndex &index, INodeView *view)
{
    if (static_cast<QueryResultItem *>(index.internalPointer())->isProperty())
    {
        QueryResultPropertyItem *item = static_cast<QueryResultPropertyItem *>(index.internalPointer());

        if (m_container.transaction())
        {
            EntityValueReader reader(m_container.entityValues(item->property().entity));
            SelectableValueListDialog dialog(m_container, reader, Application::mainWindow());

            if (dialog.exec() == SelectableValueListDialog::Accepted)
            {
                EntityValue value = dialog.takeValue();

                if (m_container.addValue(static_cast<QueryResultRootItem *>(item->parent())->value(), value))
                    if (m_container.commit())
//                        if (item->property().entity.type() == Database::Path)
//                        {
//                            beginInsertRows(index, item->size(), item->size());
//                            static_cast<QueryResultPathPropertyItem *>(item)->add(m_container.container(), value);
//                            endInsertRows();
//                        }
//                        else
                        {
                            beginInsertRows(index, item->size(), item->size());
                            item->add(value);
                            endInsertRows();
                        }
                    else
                    {
                        QMessageBox::critical(Application::mainWindow(), tr("Error"), toUnicode(m_container.lastError()));
                        m_container.rollback();
                    }
                else
                {
                    QMessageBox::critical(Application::mainWindow(), tr("Error"), toUnicode(m_container.lastError()));
                    m_container.rollback();
                }
            }
            else
                m_container.rollback();
        }
        else
            QMessageBox::critical(Application::mainWindow(), tr("Error"), toUnicode(m_container.lastError()));
    }
}