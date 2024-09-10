ProcessorGraphicsItem::ProcessorGraphicsItem(Processor* processor)
    : ProcessorObserver()
    , LabelGraphicsItemObserver()
    , processor_(processor)
    , processorMeta_(nullptr)
    , progressItem_(nullptr)
    , statusItem_(nullptr)
    , linkItem_(nullptr)
    , highlight_(false)
    #if IVW_PROFILING
    , processCount_(0)
    , countLabel_(nullptr)
    , maxEvalTime_(0.0)
    , evalTime_(0.0)
    , totEvalTime_(0.0)
    #endif
{

    setZValue(PROCESSORGRAPHICSITEM_DEPTH);
    setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable | ItemSendsGeometryChanges);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setRect(-width / 2, -height / 2, width, height);
    QGraphicsDropShadowEffect* processorShadowEffect = new QGraphicsDropShadowEffect();
    processorShadowEffect->setOffset(3.0);
    processorShadowEffect->setBlurRadius(3.0);
    setGraphicsEffect(processorShadowEffect);
    nameLabel_ = new LabelGraphicsItem(this);
    nameLabel_->setCrop(9, 8);
    nameLabel_->setPos(-width / 2.0 + labelHeight, -height / 2.0 + 0.6 * labelHeight);
    nameLabel_->setDefaultTextColor(Qt::white);
    QFont nameFont("Segoe", labelHeight, QFont::Black, false);
    nameFont.setPixelSize(pointSizeToPixelSize(labelHeight));
    nameLabel_->setFont(nameFont);
    LabelGraphicsItemObserver::addObservation(nameLabel_);
    classLabel_ = new LabelGraphicsItem(this);
    classLabel_->setCrop(9, 8);
    classLabel_->setPos(-width / 2.0 + labelHeight, -height / 2.0 + labelHeight * 2.0);
    classLabel_->setDefaultTextColor(Qt::lightGray);
    QFont classFont("Segoe", labelHeight, QFont::Normal, true);
    classFont.setPixelSize(pointSizeToPixelSize(labelHeight));
    classLabel_->setFont(classFont);

    nameLabel_->setText(QString::fromStdString(processor_->getIdentifier()));
    classLabel_->setText(QString::fromStdString(processor_->getDisplayName() + " " 
        + processor_->getTags().getString()));
    processor_->ProcessorObservable::addObserver(this);

    processorMeta_ = processor->getMetaData<ProcessorMetaData>(ProcessorMetaData::CLASS_IDENTIFIER);
    processorMeta_->addObserver(this);

    linkItem_ = new ProcessorLinkGraphicsItem(this);


    std::vector<Inport*> inports = processor_->getInports();
    std::vector<Outport*> outports = processor_->getOutports();

    inportX = rect().left() + 12.5f;
    inportY = rect().top() + 4.5f;
    outportX = rect().left() + 12.5f;
    outportY = rect().bottom() - 4.5f;

    for (auto& inport : inports) {
        addInport(inport);
    }

    for (auto& outport : outports) {
        addOutport(outport);
    }

    statusItem_ = new ProcessorStatusGraphicsItem(this, processor_);
    if (auto progressBarOwner = dynamic_cast<ProgressBarOwner*>(processor_)) {
        progressItem_ =
            new ProcessorProgressGraphicsItem(this, &(progressBarOwner->getProgressBar()));

        progressBarOwner->getProgressBar().ActivityIndicator::addObserver(statusItem_);
    }
        
    
    
    if (auto activityInd = dynamic_cast<ActivityIndicatorOwner*>(processor_)){
        activityInd->getActivityIndicator().addObserver(statusItem_);
    }

    #if IVW_PROFILING
    countLabel_ = new LabelGraphicsItem(this);
    countLabel_->setCrop(9,8);
    countLabel_->setPos(rect().left() + labelHeight, height / 2 - labelHeight*2.5);
    countLabel_->setDefaultTextColor(Qt::lightGray);
    countLabel_->setFont(classFont);
    countLabel_->setTextWidth(width - 2*labelHeight);
    #endif

    setVisible(processorMeta_->isVisible());
    setSelected(processorMeta_->isSelected());
    setPos(QPointF(processorMeta_->getPosition().x, processorMeta_->getPosition().y));
}