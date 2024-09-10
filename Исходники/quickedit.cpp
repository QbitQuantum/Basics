void QuickEdit::MoveMarked(bool before)
{
    QModelIndex current = ui->tvEditor->currentIndex();

    if(!current.isValid())
        return;

    TreeItemInterface *itemAsInterface = static_cast<TreeItemInterface*>(current.internalPointer());
    BrowserNode* currentNode = static_cast<BrowserNode*>(itemAsInterface->InternalPointer());

    //next we reorganize nodes in parent
    TreeItemInterface* parentInterface = itemAsInterface->parent();
    QList<QSharedPointer<TreeItemInterface>> children = parentInterface->GetChildren();
    QList<QSharedPointer<TreeItemInterface>> markedChildren;
    // we store all marked nodes
    QList<BrowserNode*> parentList;
    for(QSharedPointer<TreeItemInterface> child : children)
    {
        BrowserNode* childNode = static_cast<BrowserNode*>(child->InternalPointer());
        if(!parentList.contains(static_cast<BrowserNode*>(childNode->parent())))
            parentList.append(static_cast<BrowserNode*>(childNode->parent()));
        if(childNode->markedp())
            markedChildren.append(child);
    }

    if(parentList.size() > 1)
        return;

    // remove all marked from children
    for(QSharedPointer<TreeItemInterface> child : markedChildren)
    {
        children.remove(child);
    }
    //get the new position of origin node
    int newPositionOfCurrent = -1;
    for(QSharedPointer<TreeItemInterface> child : children)
    {
        newPositionOfCurrent++;
        BrowserNode* childNode = static_cast<BrowserNode*>(child->InternalPointer());
        if(childNode == currentNode)
        {
            if(!before)
                newPositionOfCurrent++;
            break;
        }
    }
    //insert the nodes back
    std::reverse(markedChildren.begin(), markedChildren.end());
    for(QSharedPointer<TreeItemInterface> child : markedChildren)
    {
        children.insert(newPositionOfCurrent, child);
    }

    QSharedPointer<TreeItemInterface> sharedOfOperation = GetSharedOfOperation(current.parent());
    TreeItem<BrowserNode>* operationItemAsNode = static_cast<TreeItem<BrowserNode>*>(sharedOfOperation.data());
    // reorganize params vector

    BrowserOperation* operationNode = static_cast<BrowserOperation*>(operationItemAsNode->InternalPointer());
    OperationData* operationData = static_cast<OperationData*>(operationNode->get_data());
    operationData->params.clear();
    for(QSharedPointer<TreeItemInterface> child : children)
    {
        BrowserOperationAttribute* attributeNode = static_cast<BrowserOperationAttribute*>(child->InternalPointer());
        operationData->params.append(attributeNode->get_param());
    }

    // install children back
    QModelIndex parentIndex = current.parent();
    treeModel->removeRows(0 , children.count(), parentIndex);
    treeModel->insertRows(0 , children.count(), parentIndex);
    int pos = -1;
    for(QSharedPointer<TreeItemInterface> child : children)
    {
        pos++;
        QModelIndex newItem = treeModel->index(pos,0,parentIndex);
        if(!newItem.isValid())
            continue;
        TreeItemInterface *newItemInterface = static_cast<TreeItemInterface*>(newItem.internalPointer());
        TreeItem<BrowserNode>* newItemAsNode = static_cast<TreeItem<BrowserNode>*>(newItemInterface);
        newItemAsNode->SetController(operationAttributeController);
        newItemAsNode->SetParent(sharedOfOperation);
        newItemAsNode->SetInternalData(static_cast<BrowserNode*>(child->InternalPointer()));
    }
    pos = -1;
    for(QSharedPointer<TreeItemInterface> child : children)
    {
        pos++;
        QModelIndex newItem = treeModel->index(pos,0,parentIndex);
        if(!newItem.isValid())
            continue;
        BrowserNode* node = static_cast<BrowserNode*>(child->InternalPointer());
        node->set_marked(false);
    }

    QModelIndex newItem = treeModel->index(pos,0,parentIndex);
    if(newItem.isValid())
        pos++;
    operationNode->modified();

}