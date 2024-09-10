void MAdvancedListItemPrivate::createLayout()
{
    Q_Q(MAdvancedListItem);

    switch (listItemStyle) {
    case MAdvancedListItem::IconWithTitleProgressIndicatorAndTwoSideIcons: {
            layout()->addItem(q->imageWidget(), 0, 0, 3, 1);

            layout()->addItem(q->titleLabelWidget(), 0, 1);
            layout()->addItem(q->progressIndicator(), 1, 1);

            QGraphicsWidget * panel = new QGraphicsWidget(q);
            QGraphicsLinearLayout * panelLayout = new QGraphicsLinearLayout(Qt::Vertical);
            panelLayout->setContentsMargins(0, 0, 0, 0);
            panelLayout->setSpacing(0);
            panel->setLayout(panelLayout);

            q->sideTopImageWidget()->setParentItem(panel);
            q->sideBottomImageWidget()->setParentItem(panel);

            panelLayout->addItem(q->sideTopImageWidget());
            panelLayout->addItem(q->sideBottomImageWidget());

            layout()->addItem(panel, 0, 2, 3, 1, Qt::AlignVCenter);
            layout()->addItem(new QGraphicsWidget(q), 2, 1);

            break;
        }
    case MAdvancedListItem::IconWithTitleProgressIndicatorAndTopSideIcon: {
            q->sideTopImageWidget()->setParentItem(q);
            q->sideBottomImageWidget()->setParentItem(q);

            layout()->addItem(q->imageWidget(), 0, 0, 3, 1);
            layout()->addItem(q->titleLabelWidget(), 0, 1);
            layout()->addItem(q->progressIndicator(), 1, 1, 1, 2);
            layout()->addItem(q->sideTopImageWidget(), 0, 2, Qt::AlignBottom);
            layout()->addItem(new QGraphicsWidget(q), 2, 1);
            break;
        }
    default:
        break;
    }
}