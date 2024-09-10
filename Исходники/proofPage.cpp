ProofPage::ProofPage(ResizableStackedWidget *pageStack, Model *model, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;



    proofEditForm = new ProofForm();
    proofEditDialog = new Dialog(this, proofEditForm, "Edit the proof...", "Change", "Cancel");

    proofDeleteDialog = new Dialog(this, nullptr, "Are you sure you want to delete this proof?", "Delete", "Cancel");



    QVBoxLayout *outerLayout = new QVBoxLayout(this);



    //  ##   ## #######   ###   #####   ####### #####
    //  ##   ## ##       ## ##  ##  ##  ##      ##  ##
    //  ##   ## ##      ##   ## ##   ## ##      ##   ##
    //  ####### #####   ##   ## ##   ## #####   ##  ##
    //  ##   ## ##      ####### ##   ## ##      #####
    //  ##   ## ##      ##   ## ##  ##  ##      ##  ##
    //  ##   ## ####### ##   ## #####   ####### ##   ##

    // The breadcrumbs show the current course and provide
    // a way to go back to the courses screen.
    // It is presented like a filepath.

    QHBoxLayout *crumbBorderLayout = new QHBoxLayout();

    breadCrumbs = new BreadCrumbs(3, model, pageStack);
    breadCrumbs->setFixedWidth(700);

    crumbBorderLayout->addStretch(1);
    crumbBorderLayout->addWidget(breadCrumbs);
    crumbBorderLayout->addStretch(1);

    outerLayout->addLayout(crumbBorderLayout);



    // Now show the name of the current proof and some buttons to
    // edit it, delete it or add a new dependency.

    QHBoxLayout *topBorderLayout = new QHBoxLayout();

    QWidget *topWidget = new QWidget();
    topWidget->setFixedWidth(700);
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);

    proofLabel = new QLabel();
    proofLabel->setWordWrap(true);
    proofLabel->setScaledContents(true);

    QFont proofFont = proofLabel->font();
    proofFont.setPointSize(24);
    proofLabel->setFont(proofFont);

    trafficLight = new TrafficLight(TrafficLight::AMBER);
    trafficLight->setFixedSize(QSize(32, 32));
    QVBoxLayout *trafficLightVLayout = new QVBoxLayout();
    trafficLightVLayout->addSpacing(16);
    trafficLightVLayout->addWidget(trafficLight);

    editProofButton = new ImageButton(QPixmap(":/images/pencil_black.png"), QSize(32, 32));
    QVBoxLayout *editProofVLayout = new QVBoxLayout();
    editProofVLayout->addSpacing(16);
    editProofVLayout->addWidget(editProofButton);

    deleteProofButton = new ImageButton(QPixmap(":/images/trash_black.png"), QSize(32, 32));
    QVBoxLayout *deleteProofVLayout = new QVBoxLayout();
    deleteProofVLayout->addSpacing(16);
    deleteProofVLayout->addWidget(deleteProofButton);

    topLayout->addWidget(proofLabel);
    topLayout->addLayout(trafficLightVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(editProofVLayout);
    topLayout->addSpacing(10);
    topLayout->addLayout(deleteProofVLayout);

    topBorderLayout->addStretch(1);
    topBorderLayout->addWidget(topWidget);
    topBorderLayout->addStretch(1);
    outerLayout->addLayout(topBorderLayout);



    outerLayout->addSpacing(20);
    outerLayout->addWidget(new HorizontalSeperator(QColor(66, 139, 202), 2));
    outerLayout->addSpacing(20);



    //  ######   #####  #####   ##    ##
    //  ##   ## ##   ## ##  ###  ##  ##
    //  ##   ## ##   ## ##   ##   ####
    //  ######  ##   ## ##   ##    ##
    //  ##   ## ##   ## ##   ##    ##
    //  ##   ## ##   ## ##  ###    ##
    //  ######   #####  #####      ##

    // Use a vertical splitter to divide the areas.

    splitter = new Splitter(Qt::Vertical);
    outerLayout->addWidget(splitter);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    // The first area is a large text editing widget, this is
    // used to edit the proof's body.
    // The QTextEdit does its own scrolling.

    bodyTextEdit = new QTextEdit();

    QFont font = bodyTextEdit->font();
    font.setFamily("Courier");
    font.setPointSize(12);
    bodyTextEdit->setFont(font);

    bodyHighlighter = new LatexHighlighter(bodyTextEdit->document());

    splitter->addWidget(bodyTextEdit);

    QTimer *bodySaveTimer = new QTimer(this);
    bodySaveTimer->setSingleShot(true);
    bodySaveTimer->setInterval(200);

    connect(bodyTextEdit, SIGNAL(textChanged()), bodySaveTimer, SLOT(start()));
    connect(bodySaveTimer, SIGNAL(timeout()), this, SLOT(saveBody()));



    // The second area contains the rendered body.

    QScrollArea *bodyScrollArea = new QScrollArea();
    bodyScrollArea->setWidgetResizable(true);
    bodyScrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *bodyWidget = new QWidget();

    QPalette palette = bodyWidget->palette();
    palette.setColor(QPalette::Background, Qt::white);
    bodyWidget->setPalette(palette);
    bodyWidget->setAutoFillBackground(true);

    bodyImage = new ResizableImage("");

    QHBoxLayout *bodyHLayout = new QHBoxLayout();
    bodyHLayout->addStretch(1);
    bodyHLayout->addWidget(bodyImage);
    bodyHLayout->addStretch(1);

    QVBoxLayout *bodyVLayout = new QVBoxLayout();
    bodyVLayout->addLayout(bodyHLayout);
    bodyVLayout->addStretch(1);

    bodyWidget->setLayout(bodyVLayout);
    bodyScrollArea->setWidget(bodyWidget);
    splitter->addWidget(bodyScrollArea);



    //  #####  ####  #####  ##   ##   ###   ##       #####
    // ##   ##  ##  ##   ## ###  ##  ## ##  ##      ##   ##
    //  ##      ##  ##      ###  ## ##   ## ##       ##
    //   ###    ##  ##      ####### ##   ## ##        ###
    //     ##   ##  ##  ### ##  ### ####### ##          ##
    // ##   ##  ##  ##   ## ##  ### ##   ## ##      ##   ##
    //  #####  ####  #####  ##   ## ##   ## #######  #####

    connect(editProofButton, SIGNAL(clicked()), this, SLOT(proofEditButtonClicked()));

    connect(proofEditDialog, SIGNAL(accepted()), this, SLOT(proofEditDialogCompleted()));
    connect(proofEditDialog, SIGNAL(rejected()), proofEditDialog, SLOT(close()));

    connect(deleteProofButton, SIGNAL(clicked()), proofDeleteDialog, SLOT(show()));

    connect(proofDeleteDialog, SIGNAL(accepted()), this, SLOT(proofDeleteDialogAccepted()));
    connect(proofDeleteDialog, SIGNAL(rejected()), proofDeleteDialog, SLOT(close()));

    connect(model, SIGNAL(proofSelectedChanged(Proof)), this, SLOT(proofSelectedChangedSlot(Proof)));
    connect(model, SIGNAL(proofEdited(Proof)), this, SLOT(proofEditedSlot(Proof)));
    connect(model, SIGNAL(proofDeleted(int)), this, SLOT(proofDeletedSlot(int)));
}