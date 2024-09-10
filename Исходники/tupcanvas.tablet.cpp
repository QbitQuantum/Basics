TupCanvas::TupCanvas(QWidget *parent, Qt::WindowFlags flags, TupGraphicsScene *scene, 
                   const QPointF centerPoint, const QSize &screenSize, TupProject *project, double scaleFactor,
                   int angle, TupBrushManager *brushManager) : QFrame(parent, flags), k(new Private)
{
    setWindowTitle(tr("Tupi: 2D Magic"));
    setWindowIcon(QIcon(QPixmap(THEME_DIR + "icons/animation_mode.png")));

    k->scene = scene;
    k->size = project->dimension();
    k->currentColor = brushManager->penColor();
    k->brushManager = brushManager;
    k->project = project;

    graphicsView = new TupCanvasView(this, screenSize, k->size, project->bgColor());

    graphicsView->setScene(scene);
    graphicsView->centerOn(centerPoint);
    graphicsView->scale(scaleFactor, scaleFactor);
    graphicsView->rotate(angle);

    TImageButton *pencil = new TImageButton(QPixmap(THEME_DIR + "icons/pencil_big.png"), 40, this, true);
    pencil->setToolTip(tr("Pencil"));
    connect(pencil, SIGNAL(clicked()), this, SLOT(wakeUpPencil()));

    TImageButton *ink = new TImageButton(QPixmap(THEME_DIR + "icons/ink_big.png"), 40, this, true);
    ink->setToolTip(tr("Ink"));
    connect(ink, SIGNAL(clicked()), this, SLOT(wakeUpInk()));

    /*
    TImageButton *polyline = new TImageButton(QPixmap(THEME_DIR + "icons/polyline_big.png"), 40, this, true);
    polyline->setToolTip(tr("Polyline"));
    connect(polyline, SIGNAL(clicked()), this, SLOT(wakeUpPolyline()));
    */

    TImageButton *ellipse = new TImageButton(QPixmap(THEME_DIR + "icons/ellipse_big.png"), 40, this, true);
    ellipse->setToolTip(tr("Ellipse"));
    connect(ellipse, SIGNAL(clicked()), this, SLOT(wakeUpEllipse()));

    TImageButton *rectangle = new TImageButton(QPixmap(THEME_DIR + "icons/square_big.png"), 40, this, true);
    rectangle->setToolTip(tr("Rectangle"));
    connect(rectangle, SIGNAL(clicked()), this, SLOT(wakeUpRectangle()));

    TImageButton *images = new TImageButton(QPixmap(THEME_DIR + "icons/bitmap_big.png"), 40, this, true);
    images->setToolTip(tr("Images"));
    connect(images, SIGNAL(clicked()), this, SLOT(wakeUpLibrary()));

    TImageButton *objects = new TImageButton(QPixmap(THEME_DIR + "icons/selection_big.png"), 40, this, true);
    objects->setToolTip(tr("Object Selection"));
    connect(objects, SIGNAL(clicked()), this, SLOT(wakeUpObjectSelection()));

    TImageButton *nodes = new TImageButton(QPixmap(THEME_DIR + "icons/nodes_big.png"), 40, this, true);
    nodes->setToolTip(tr("Nodes Selection"));
    connect(nodes, SIGNAL(clicked()), this, SLOT(wakeUpNodeSelection()));

    TImageButton *trash = new TImageButton(QPixmap(THEME_DIR + "icons/delete_big.png"), 40, this, true);
    trash->setToolTip(tr("Delete Selection"));
    connect(trash, SIGNAL(clicked()), this, SLOT(wakeUpDeleteSelection()));

    TImageButton *zoomIn = new TImageButton(QPixmap(THEME_DIR + "icons/zoom_in_big.png"), 40, this, true);
    zoomIn->setToolTip(tr("Zoom In"));
    connect(zoomIn, SIGNAL(clicked()), this, SLOT(wakeUpZoomIn()));

    TImageButton *zoomOut = new TImageButton(QPixmap(THEME_DIR + "icons/zoom_out_big.png"), 40, this, true);
    zoomOut->setToolTip(tr("Zoom Out"));
    connect(zoomOut, SIGNAL(clicked()), this, SLOT(wakeUpZoomOut()));

    TImageButton *shift = new TImageButton(QPixmap(THEME_DIR + "icons/hand_big.png"), 40, this, true);
    shift->setToolTip(tr("Shift"));
    connect(shift, SIGNAL(clicked()), this, SLOT(wakeUpShift()));

    TImageButton *undo = new TImageButton(QPixmap(THEME_DIR + "icons/undo_big.png"), 40, this, true);
    undo->setToolTip(tr("Undo"));
    connect(undo, SIGNAL(clicked()), this, SLOT(undo()));

    TImageButton *redo = new TImageButton(QPixmap(THEME_DIR + "icons/redo_big.png"), 40, this, true);
    redo->setToolTip(tr("Redo"));
    connect(redo, SIGNAL(clicked()), this, SLOT(redo()));

    TImageButton *colors = new TImageButton(QPixmap(THEME_DIR + "icons/color_palette_big.png"), 40, this, true);
    colors->setToolTip(tr("Color Palette"));
    connect(colors, SIGNAL(clicked()), this, SLOT(colorDialog()));

    TImageButton *pen = new TImageButton(QPixmap(THEME_DIR + "icons/pen_properties.png"), 40, this, true);
    pen->setToolTip(tr("Pen Size"));
    connect(pen, SIGNAL(clicked()), this, SLOT(penDialog()));

    TImageButton *exposure = new TImageButton(QPixmap(THEME_DIR + "icons/exposure_sheet_big.png"), 40, this, true);
    exposure->setToolTip(tr("Exposure Sheet"));
    connect(exposure, SIGNAL(clicked()), this, SLOT(exposureDialog()));

    QBoxLayout *controls = new QBoxLayout(QBoxLayout::TopToBottom);
    controls->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    controls->setContentsMargins(3, 3, 3, 3);
    controls->setSpacing(7);

    controls->addWidget(pencil);
    controls->addWidget(ink);
    // controls->addWidget(polyline);
    controls->addWidget(ellipse);
    controls->addWidget(rectangle);
    controls->addWidget(images);
    controls->addWidget(objects);
    controls->addWidget(nodes);
    controls->addWidget(trash);
    controls->addWidget(zoomIn);
    controls->addWidget(zoomOut);
    controls->addWidget(hand);

    controls->addWidget(undo);
    controls->addWidget(redo);
    controls->addWidget(colors);
    controls->addWidget(pen);
    controls->addWidget(exposure);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    layout->addLayout(controls);
    layout->addWidget(graphicsView);

    setLayout(layout);
}