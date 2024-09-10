GraphScene::GraphScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_gridLayout(new QGraphicsGridLayout)
    , m_inDrag(false), m_dragArrow(NULL), m_dragStartNode(NULL)
    , m_inputNode(NULL), m_outputNode(NULL)
{
    setBackgroundBrush(Qt::white);

    m_gridLayout->setHorizontalSpacing(NODEITEM_PIXEL_DISTANCE); // Set up layout-related stuff
    m_gridLayout->setVerticalSpacing(NODEITEM_PIXEL_DISTANCE);
    QGraphicsWidget *form = new QGraphicsWidget;
    form->setLayout(m_gridLayout);
    addItem(form);

    init(StandardInit);                                     // Init a standard scene
}