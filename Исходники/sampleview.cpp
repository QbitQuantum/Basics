void SampleView::setupMainLayout(){

    // Create QListView object and associate it with the sample model.
    sampleListView_ = new QListView();
    sampleListView_->setModel(sampleModel_);
    // Prevent user from editing the text within the view.
    sampleListView_->setEditTriggers(0);
    // Set view to display column 4 (index 3) of the model, the sample title.
    sampleListView_->setModelColumn(3);

    // Sample list and it's groupbox layout setup.
    sampleListGroupBox_ = new QGroupBox("Samples");
    sampleListLayout_ = new QVBoxLayout;
    sampleListLayout_->addWidget(sampleListView_);
    sampleListGroupBox_->setLayout(sampleListLayout_);

    nameLabel_ = new QLabel("Sample Name: ");
    nameEdit_ = new QLineEdit();

    chemLabel_ = new QLabel("Chemical Symbol: ");
    chemEdit_ = new QLineEdit();

    notesLabel_ = new QLabel("Notes: ");
    notesEdit_ = new QTextEdit();

    addSampleButton_ = new QPushButton("Add Sample");
    removeSampleButton_ = new QPushButton("Remove Sample");

    // Setup QDataWidgetMapper. Set approrpite UI elements to their respective rows in sample model.
    // Set the widgets to display the first sample.
    modelToWidgetMapper_ = new QDataWidgetMapper(this);
    modelToWidgetMapper_->setModel(sampleModel_);
    modelToWidgetMapper_->addMapping(nameEdit_, 0);
    modelToWidgetMapper_->addMapping(chemEdit_, 1);
    modelToWidgetMapper_->addMapping(notesEdit_, 2);
    modelToWidgetMapper_->toFirst();

    //Master layout
    sampleWidgetLayout_ = new QHBoxLayout();

    //Sample sub-layout
    sampleNameLayout_ = new QHBoxLayout();
    sampleChemLayout_ = new QHBoxLayout();
    sampleNotesLayout_ = new QHBoxLayout();
    sampleInfoLayout_ = new QVBoxLayout();
    addRemoveButtonLayout_ = new QHBoxLayout();

    //Add widgets to appropriate layouts
    sampleNameLayout_->addWidget(nameLabel_);
    sampleNameLayout_->addWidget(nameEdit_);

    sampleChemLayout_->addWidget(chemLabel_);
    sampleChemLayout_->addWidget(chemEdit_);

    sampleNotesLayout_->addWidget(notesLabel_);
    sampleNotesLayout_->addWidget(notesEdit_);

    addRemoveButtonLayout_->addWidget(addSampleButton_);
    addRemoveButtonLayout_->addWidget(removeSampleButton_);

    sampleInfoLayout_->addLayout(sampleNameLayout_);
    sampleInfoLayout_->addLayout(sampleChemLayout_);
    sampleInfoLayout_->addLayout(sampleNotesLayout_);
    sampleInfoLayout_->addLayout(addRemoveButtonLayout_);

    //Setup master layout
    sampleWidgetLayout_->addLayout(sampleInfoLayout_);
    sampleWidgetLayout_->addSpacing(10);
    sampleWidgetLayout_->addWidget(sampleListGroupBox_);

    setLayout(sampleWidgetLayout_);

}