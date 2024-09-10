GEvScene::GEvScene(GSequence *parentSeq)
    : QGraphicsScene(parentSeq)
    , m_pSeq(parentSeq)
{
    // to have the scene match the sequence length
    connect(m_pSeq, SIGNAL(LengthChanged(double)), this, SLOT(UpdateLength(double)), Qt::QueuedConnection);

    // background color
    setBackgroundBrush(QColor(230, 255, 230));

    // this is a QGraphicsWidget to use a layout in the scene
    QGraphicsWidget* pGraWid = new QGraphicsWidget();
    addItem(pGraWid);
    m_pChannelLayout = new QGraphicsLinearLayout(Qt::Vertical);
    pGraWid->setLayout(m_pChannelLayout);
    // margins from the view border
    m_pChannelLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    // spacing between channels
    m_pChannelLayout->setSpacing(1.0);

    // makes the root item, parent of all event in the sequence
    m_pRootEvent = new GSynchEvent(0);
    m_pRootEvent->setParent(this);
    m_pRootEvent->setFlag(QGraphicsItem::ItemIsMovable, false);;
    addItem(m_pRootEvent);
}