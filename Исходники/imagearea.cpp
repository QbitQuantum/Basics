ImageArea::ImageArea(const bool &isOpen, const QString &filePath, QWidget *parent) :
    QWidget(parent), mIsEdited(false), mIsPaint(false), mIsResize(false)
{
    setMouseTracking(true);

    mRightButtonPressed = false;
    mFilePath.clear();
    makeFormatsFilters();
    initializeImage();
    mZoomFactor = 1;

    mAdditionalTools = new AdditionalTools(this);

    mUndoStack = new QUndoStack(this);
    mUndoStack->setUndoLimit(DataSingleton::Instance()->getHistoryDepth());

    if(isOpen && filePath.isEmpty())
    {
        open();
    }
    else if(isOpen && !filePath.isEmpty())
    {
        open(filePath);
    }
    else
    {
        QPainter *painter = new QPainter(mImage);
        painter->fillRect(0, 0,
                          DataSingleton::Instance()->getBaseSize().width(),
                          DataSingleton::Instance()->getBaseSize().height(),
                          Qt::white);
        painter->end();

        resize(mImage->rect().right() + 6,
               mImage->rect().bottom() + 6);
    }

    QTimer *autoSaveTimer = new QTimer(this);
    autoSaveTimer->setInterval(DataSingleton::Instance()->getAutoSaveInterval() * 1000);
    connect(autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));
    connect(mAdditionalTools, SIGNAL(sendNewImageSize(QSize)), this, SIGNAL(sendNewImageSize(QSize)));

    autoSaveTimer->start();

    SelectionInstrument *selectionInstrument = new SelectionInstrument(this);
    connect(selectionInstrument, SIGNAL(sendEnableCopyCutActions(bool)), this, SIGNAL(sendEnableCopyCutActions(bool)));
    connect(selectionInstrument, SIGNAL(sendEnableSelectionInstrument(bool)), this, SIGNAL(sendEnableSelectionInstrument(bool)));

    // Instruments handlers
    mInstrumentsHandlers.fill(0, (int)INSTRUMENTS_COUNT);
    mInstrumentsHandlers[CURSOR] = selectionInstrument;
    mInstrumentsHandlers[PEN] = new PencilInstrument(this);
    mInstrumentsHandlers[LINE] = new LineInstrument(this);
    mInstrumentsHandlers[ERASER] = new EraserInstrument(this);
    mInstrumentsHandlers[RECTANGLE] = new RectangleInstrument(this);
    mInstrumentsHandlers[ELLIPSE] = new EllipseInstrument(this);
    mInstrumentsHandlers[FILL] = new FillInstrument(this);
    mInstrumentsHandlers[SPRAY] = new SprayInstrument(this);
    mInstrumentsHandlers[MAGNIFIER] = new MagnifierInstrument(this);
    mInstrumentsHandlers[COLORPICKER] = new ColorpickerInstrument(this);
    mInstrumentsHandlers[CURVELINE] = new CurveLineInstrument(this);
    mInstrumentsHandlers[TEXT] = new TextInstrument(this);

    // Effects handlers
    mEffectsHandlers.fill(0, (int)EFFECTS_COUNT);
    mEffectsHandlers[NEGATIVE] = new NegativeEffect(this);
    mEffectsHandlers[GRAY] = new GrayEffect(this);
    mEffectsHandlers[BINARIZATION] = new BinarizationEffect(this);
    mEffectsHandlers[GAUSSIANBLUR] = new GaussianBlurEffect(this);
    mEffectsHandlers[GAMMA] = new GammaEffect(this);
    mEffectsHandlers[SHARPEN] = new SharpenEffect(this);
    mEffectsHandlers[CUSTOM] = new CustomEffect(this);
}