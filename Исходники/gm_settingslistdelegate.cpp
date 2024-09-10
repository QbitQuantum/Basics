void GM_SettingsListDelegate::paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 opt = option;
    initStyleOption(&opt, index);

    const QWidget* w = opt.widget;
    const QStyle* style = w ? w->style() : QApplication::style();
    const Qt::LayoutDirection direction = w ? w->layoutDirection() : QApplication::layoutDirection();
    const int height = opt.rect.height();
    const int center = height / 2 + opt.rect.top();

    // Prepare title font
    QFont titleFont = opt.font;
    titleFont.setBold(true);
    titleFont.setPointSize(titleFont.pointSize() + 1);

    const QFontMetrics titleMetrics(titleFont);
#ifdef Q_OS_WIN
    const QPalette::ColorRole colorRole = QPalette::Text;
#else
    const QPalette::ColorRole colorRole = opt.state & QStyle::State_Selected ? QPalette::HighlightedText : QPalette::Text;
#endif

    int leftPosition = m_padding;
    int rightPosition = opt.rect.right() - m_padding - 16; // 16 for remove button

    // Draw background
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter, w);

    // Draw checkbox
    const int checkboxSize = 18;
    const int checkboxYPos = center - (checkboxSize / 2);
    QStyleOptionViewItemV4 opt2 = opt;
    opt2.checkState == Qt::Checked ? opt2.state |= QStyle::State_On : opt2.state |= QStyle::State_Off;
    QRect styleCheckBoxRect = style->subElementRect(QStyle::SE_ViewItemCheckIndicator, &opt2, w);
    styleCheckBoxRect.setRect(leftPosition, checkboxYPos, styleCheckBoxRect.width(), styleCheckBoxRect.height());
    QRect visualCheckBoxRect = style->visualRect(direction, opt.rect, styleCheckBoxRect);
    opt2.rect = visualCheckBoxRect;
    style->drawPrimitive(QStyle::PE_IndicatorViewItemCheck, &opt2, painter, w);
    leftPosition = styleCheckBoxRect.right() + m_padding;

    // Draw icon
    const int iconSize = 32;
    const int iconYPos = center - (iconSize / 2);
    QRect iconRect(leftPosition, iconYPos, iconSize, iconSize);
    QRect visualIconRect = style->visualRect(direction, opt.rect, iconRect);
    QPixmap pixmap = index.data(Qt::DecorationRole).value<QIcon>().pixmap(iconSize);
    painter->drawPixmap(visualIconRect, pixmap);
    leftPosition = iconRect.right() + m_padding;

    // Draw script name
    const QString &name = index.data(Qt::DisplayRole).toString();
    const int leftTitleEdge = leftPosition + 2;
    const int rightTitleEdge = rightPosition - m_padding;
    const int leftPosForVersion = titleMetrics.width(name) + m_padding;
    QRect nameRect(leftTitleEdge, opt.rect.top() + m_padding, rightTitleEdge - leftTitleEdge, titleMetrics.height());
    QRect visualNameRect = style->visualRect(direction, opt.rect, nameRect);
    painter->setFont(titleFont);
    style->drawItemText(painter, visualNameRect, Qt::AlignLeft, opt.palette, true, name, colorRole);

    // Draw version
    const QString &version = index.data(Qt::UserRole).toString();
    QRect versionRect(nameRect.x() + leftPosForVersion, nameRect.y(), rightTitleEdge - leftPosForVersion, titleMetrics.height());
    QFont versionFont = titleFont;
    versionFont.setBold(false);
    painter->setFont(versionFont);
    style->drawItemText(painter, versionRect, Qt::AlignLeft, opt.palette, true, version, colorRole);

    // Draw description
    const int infoYPos = nameRect.bottom() + opt.fontMetrics.leading();
    QRect infoRect(visualNameRect.x(), infoYPos, nameRect.width(), opt.fontMetrics.height());
    const QString &info = opt.fontMetrics.elidedText(index.data(Qt::UserRole + 1).toString(), Qt::ElideRight, infoRect.width());
    painter->setFont(opt.font);
    style->drawItemText(painter, infoRect, Qt::TextSingleLine | Qt::AlignLeft, opt.palette, true, info, colorRole);

    // Draw remove button
    const int removeIconSize = 16;
    const int removeIconYPos = center - (removeIconSize / 2);
    QRect removeIconRect(rightPosition, removeIconYPos, removeIconSize, removeIconSize);
    QRect visualRemoveIconRect = style->visualRect(direction, opt.rect, removeIconRect);
    painter->drawPixmap(visualRemoveIconRect, m_removePixmap);
}