void ApplicationsWindow::rebuildApplicationsList()
{
    //create categories
    QVector<QTreeWidgetItem*> categories;
    categories.resize(m_DataManager->categoriesCount());
    ui->treeWidgetApplications->clear();
    for (int i = 0; i<m_DataManager->categoriesCount(); i++){
        const sCategory* category = m_DataManager->categories(i);
        categories[i] = createTreeItemCategory(i,category->color,category->name);
        categories[i]->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
        ui->treeWidgetApplications->addTopLevelItem(categories[i]);

    }
    QTreeWidgetItem* uncategorized = createTreeItemCategory(-1,QColor(Qt::gray),tr("Uncategorized"));
    uncategorized->setFlags(Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
    ui->treeWidgetApplications->addTopLevelItem(uncategorized);

    //place applications in category
    int currentProfile = m_DataManager->getCurrentProfileIndex();
    for (int i = 0; i<m_DataManager->applicationsCount(); i++){
        const sAppInfo* app = m_DataManager->applications(i);

        QTreeWidgetItem* item = new QTreeWidgetItem(cApplicationsTreeWidget::TREE_ITEM_TYPE_APPLICATION);
        item->setText(0,app->name);
        item->setToolTip(0,app->path+"/"+app->name);
        item->setData(0,Qt::UserRole,i);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
        if (app->categories[currentProfile]==-1)
            uncategorized->addChild(item);
        else
            categories[app->categories[currentProfile]]->addChild(item);
    }

    //expand all categories
    uncategorized->setExpanded(true);
    for (int i = 0; i<categories.size(); i++)
        categories[i]->setExpanded(true);
}