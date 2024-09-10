void NameItemDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &styleOption,
                             const QModelIndex &modelIndex) const
{
    painter->save();
    if (styleOption.state & QStyle::State_Selected)
        NavigatorTreeView::drawSelectionBackground(painter, styleOption);

    int iconOffset = drawIcon(painter, styleOption, modelIndex);

    QRect textFrame = drawText(painter, styleOption, modelIndex, iconOffset);

    if (modelIndex.data(NavigatorTreeModel::ErrorRole).toBool())
        drawRedWavyUnderLine(painter, styleOption, textFrame);

    painter->restore();
}