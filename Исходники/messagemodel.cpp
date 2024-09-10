QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();

    ContextItem *cntxtItem = static_cast<ContextItem *>(index.internalPointer());
    if (cntxtItem) {
        if (row >= cntxtItem->messageItemsInList() || !index.isValid())
            return QVariant();

        MessageItem *msgItem = cntxtItem->messageItem(row);

        if (role == Qt::DisplayRole) {
            switch(column) {
            case 0: // done
                return QVariant();
            case 1: // source text
			    return msgItem->sourceText().simplified();
            case 2: // translation
                return msgItem->translation().simplified();
            }
        }
        else if ((role == Qt::DecorationRole) && (column == 0)) {
            if (msgItem->message().type() == MetaTranslatorMessage::Unfinished && msgItem->translation().isEmpty())
                return qVariantFromValue(*TrWindow::pxEmpty);
            else if (msgItem->message().type() == MetaTranslatorMessage::Unfinished && msgItem->danger())
                return qVariantFromValue(*TrWindow::pxDanger);
            else if (msgItem->message().type() == MetaTranslatorMessage::Finished && msgItem->danger())
                return qVariantFromValue(*TrWindow::pxWarning);
            else if (msgItem->message().type() == MetaTranslatorMessage::Finished)
                return qVariantFromValue(*TrWindow::pxOn);
            else if (msgItem->message().type() == MetaTranslatorMessage::Unfinished)
                return qVariantFromValue(*TrWindow::pxOff);
            else if (msgItem->message().type() == MetaTranslatorMessage::Obsolete)
                return qVariantFromValue(*TrWindow::pxObsolete);
        }
    } else {
        if (row >= cntxtList.count() || !index.isValid())
            return QVariant();

        ContextItem *cntxtItem = cntxtList.at(row);

        if (role == Qt::DisplayRole) {
            switch(column) {
            case 0: // done
                return QVariant();
            case 1: // context
                return cntxtItem->context().simplified();
            case 2: // items
                QString s;
                int itemCount = cntxtItem->messageItemsInList();
                int obsoleteCount = cntxtItem->obsolete();
                int finishedCount = cntxtItem->finishedCount();
                s.sprintf("%d/%d", finishedCount,
                    itemCount - obsoleteCount);
                return s;
            }
        }
        else if ((role == Qt::DecorationRole) && (column == 0)) {
            if (cntxtItem->isContextObsolete())
                return qVariantFromValue(*TrWindow::pxObsolete);
            else if (cntxtItem->isFinished())
                return qVariantFromValue(*TrWindow::pxOn);
            else
                return qVariantFromValue(*TrWindow::pxOff);
        }
    }
    return QVariant();
}