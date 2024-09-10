QTreeWidgetItem* FunctionsTreeWidget::parentItem(const Function* function)
{
    Q_ASSERT(function != NULL);

    // Special case for Sequences. They belong to a Scene node
    if (function->type() == Function::Chaser && qobject_cast<const Chaser*>(function)->isSequence() == true)
    {
        quint32 sid = qobject_cast<const Chaser*>(function)->getBoundSceneID();
        Function *sceneFunc = m_doc->function(sid);
        if (sceneFunc != NULL)
        {
            QTreeWidgetItem *sceneTopItem = folderItem(sceneFunc->path());
            if (sceneTopItem != NULL)
            {
                for (int i = 0; i < sceneTopItem->childCount(); i++)
                {
                    QTreeWidgetItem *child = sceneTopItem->child(i);
                    Q_ASSERT(child != NULL);

                    if (sid == itemFunctionId(child))
                        return child;
                }
            }
        }
    }

    QString basePath = Function::typeToString(function->type());
    if (m_foldersMap.contains(QString(basePath + "/")) == false)
    {
        // Parent item for the given type doesn't exist yet so create one
        QTreeWidgetItem* item = new QTreeWidgetItem(this);
        item->setText(COL_NAME, basePath);
        item->setIcon(COL_NAME, functionIcon(function));
        item->setData(COL_NAME, Qt::UserRole, Function::invalidId());
        item->setData(COL_NAME, Qt::UserRole + 1, function->type());
        item->setText(COL_PATH, QString(basePath + "/"));
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled);
        m_foldersMap[QString(basePath + "/")] = item;
    }

    QTreeWidgetItem *pItem = folderItem(function->path());

    if (pItem != NULL)
    {
        //qDebug() << "Found item for function:" << function->name() << ", path: " << function->path();
        return pItem;
    }


    return NULL;
}