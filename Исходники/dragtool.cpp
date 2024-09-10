void DragTool::dropEvent(const QList<QGraphicsItem*> &/*itemList*/, QGraphicsSceneDragDropEvent *event)
{
    if (canHandleMimeData(event->mimeData())) {
        event->accept();
        end(generateUseSnapping(event->modifiers()));

        commitTransaction();

        if (m_dragNode.isValid())
            view()->setSelectedModelNode(m_dragNode);


        m_dragNode = QmlItemNode();

        view()->changeToSelectionTool();
    }
}