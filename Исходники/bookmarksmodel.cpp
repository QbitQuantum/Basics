bool BookmarksModel::dropMimeData(const QMimeData *data,
                                  Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (column > 0)
        return false;

    BookmarkNode *parentNode = node(parent);

    if (!data->hasFormat(MIMETYPE)) {
        if (!data->hasUrls())
            return false;

        BookmarkNode *node = new BookmarkNode(BookmarkNode::Bookmark, parentNode);
        node->url = QString::fromUtf8(data->urls().at(0).toEncoded());

        if (data->hasText())
            node->title = data->text();
        else
            node->title = node->url;

        m_bookmarksManager->addBookmark(parentNode, node, row);
        return true;
    }

    QByteArray ba = data->data(MIMETYPE);
    QDataStream stream(&ba, QIODevice::ReadOnly);
    if (stream.atEnd())
        return false;

    QUndoStack *undoStack = m_bookmarksManager->undoRedoStack();
    undoStack->beginMacro(QLatin1String("Move Bookmarks"));

    while (!stream.atEnd()) {
        QByteArray encodedData;
        stream >> encodedData;
        QBuffer buffer(&encodedData);
        buffer.open(QBuffer::ReadOnly);

        XbelReader reader;
        BookmarkNode *rootNode = reader.read(&buffer);
        QList<BookmarkNode*> children = rootNode->children();
        for (int i = 0; i < children.count(); ++i) {
            BookmarkNode *bookmarkNode = children.at(i);
            rootNode->remove(bookmarkNode);
            row = qMax(0, row);
            m_bookmarksManager->addBookmark(parentNode, bookmarkNode, row);
            m_endMacro = true;
        }
        delete rootNode;
    }
    return true;
}