void VDirectoryTree::updateItemDirectChildren(QTreeWidgetItem *p_item)
{
    QPointer<VDirectory> parentDir;
    if (p_item) {
        parentDir = getVDirectory(p_item);
    } else {
        parentDir = m_notebook->getRootDir();
    }

    const QVector<VDirectory *> &dirs = parentDir->getSubDirs();

    QHash<VDirectory *, QTreeWidgetItem *> itemDirMap;
    int nrChild = p_item ? p_item->childCount() : topLevelItemCount();
    for (int i = 0; i < nrChild; ++i) {
        QTreeWidgetItem *item = p_item ? p_item->child(i) : topLevelItem(i);
        itemDirMap.insert(getVDirectory(item), item);
    }

    for (int i = 0; i < dirs.size(); ++i) {
        VDirectory *dir = dirs[i];
        QTreeWidgetItem *item = itemDirMap.value(dir, NULL);
        if (item) {
            if (p_item) {
                p_item->removeChild(item);
                p_item->insertChild(i, item);
            } else {
                int topIdx = indexOfTopLevelItem(item);
                takeTopLevelItem(topIdx);
                insertTopLevelItem(i, item);
            }

            itemDirMap.remove(dir);
        } else {
            // Insert a new item
            if (p_item) {
                item = new QTreeWidgetItem(p_item);
            } else {
                item = new QTreeWidgetItem(this);
            }

            fillTreeItem(item, dir);
            buildSubTree(item, 1);
        }

        expandSubTree(item);
    }

    // Delete items without corresponding VDirectory
    for (auto iter = itemDirMap.begin(); iter != itemDirMap.end(); ++iter) {
        QTreeWidgetItem *item = iter.value();
        if (p_item) {
            p_item->removeChild(item);
        } else {
            int topIdx = indexOfTopLevelItem(item);
            takeTopLevelItem(topIdx);
        }

        delete item;
    }
}