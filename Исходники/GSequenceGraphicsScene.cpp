GSequenceGraphicsScene::GSequenceGraphicsScene(GSequence *parentSeq)
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
	m_pChanLay = new QGraphicsLinearLayout(Qt::Vertical);
	pGraWid->setLayout(m_pChanLay);
	// margins from the view border
	m_pChanLay->setContentsMargins(0.0, 0.0, 0.0, 0.0);
	// spacing between channels
	m_pChanLay->setSpacing(1.0);
}