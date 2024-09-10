/*
This function initializes the IFSOperationViewer and gets the inherited main window ready.
*/
IFSOperationViewer::IFSOperationViewer()
{
loadedIFSImage = NULL;
setupUi(this);

//Setup IFSImageLabels
leftImageLabel = new IFSImageLabel(imageFrame);
leftImageLabel->setObjectName(QString::fromUtf8("leftImageLabel"));
leftImageLabel->setScaledContents(false);
leftImageLabel->setAlignment(Qt::AlignCenter);

horizontalLayout_2->addWidget(leftImageLabel);

rightImageLabel = new IFSImageLabel(imageFrame);
rightImageLabel->setObjectName(QString::fromUtf8("rightImageLabel"));
rightImageLabel->setAlignment(Qt::AlignCenter);

horizontalLayout_2->addWidget(rightImageLabel);

//Set the slider for 3D images invisible until it is needed
threeDFramePositionLabel->setHidden(true);
threeDFramePositionSlider->setHidden(true);





//Initialize the file open action
action_Open->setShortcut(QKeySequence::Open);
action_Open->setStatusTip(tr("Load a IFS image for processing and viewing"));

//Initialize the save action
action_Save->setShortcut(QKeySequence::Save);
action_Save->setStatusTip(tr("Save the result of processing"));

//Connect the image labels to the values for the position
connect(leftImageLabel, SIGNAL(imageCursorRow(int)), rowPositionLabel, SLOT(setNum(int)));
connect(rightImageLabel, SIGNAL(imageCursorRow(int)), rowPositionLabel, SLOT(setNum(int)));

connect(leftImageLabel, SIGNAL(imageCursorColumn(int)), columnPositionLabel, SLOT(setNum(int)));
connect(rightImageLabel, SIGNAL(imageCursorColumn(int)), columnPositionLabel, SLOT(setNum(int)));

connect(leftImageLabel, SIGNAL(imageCursorValue(double)), imageValueLabel, SLOT(setNum(double)));
connect(rightImageLabel, SIGNAL(imageCursorValue(double)), imageValueLabel, SLOT(setNum(double)));

//Add action signals
connect(action_Open, SIGNAL(triggered()), this, SLOT(openFile()));
connect(action_Save, SIGNAL(triggered()), this, SLOT(saveFile()));

//Connect buttons
connect(applyButton, SIGNAL(clicked()), this, SLOT(applyOperation()));
connect(swapButton, SIGNAL(clicked()), this, SLOT(swap()));

//Connect slider
connect(threeDFramePositionSlider, SIGNAL(valueChanged(int)), this, SLOT(setFrame(int)));
connect(threeDFramePositionSlider, SIGNAL(valueChanged(int)), threeDFramePositionLabel, SLOT(setNum(int)));

//Set up function details and the function list
populateFunctionDetailsAndList();

//Connect list to parameters
connect(operationListBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(setupParameterWidgets(const QString&)));

//Set the function list to the first item
if(operationListBox->count() > 0)
{
operationListBox->setCurrentRow(0);
}

}