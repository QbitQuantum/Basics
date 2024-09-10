QtSyncStatusLogView::QtSyncStatusLogView(QtSyncStatusLog& log, QGraphicsItem *parent)
    : HbView(parent),
      mSyncLog(log)
{
    setTitle("QtSyncStatusSpy");
    createMenu();
    
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Vertical);
    HbScrollArea* scrollArea = new HbScrollArea(this);
    scrollArea->setScrollDirections(Qt::Vertical);
    QGraphicsLinearLayout* layout2 = new QGraphicsLinearLayout(Qt::Vertical);
    QGraphicsWidget* content = new QGraphicsWidget(this);
    
    mTextItem = new HbTextItem();
    layout2->addItem(mTextItem);
    layout2->setContentsMargins(5, 5, 5, 5);
    content->setLayout(layout2);
    scrollArea->setContentWidget(content);

    layout->addItem(scrollArea);
    layout->setStretchFactor(scrollArea, 1);
    setLayout(layout);
}