// Constructor
FusionDialog::FusionDialog(QWidget* parent) : Dialog(parent)
{
    setWindowTitle("Fusion");

    // Create the interface
    QVBoxLayout* vLayout = new QVBoxLayout();

    m_addMergedSeriesButton = new PushButton("Ajouter une fusion");
    vLayout->addWidget(m_addMergedSeriesButton);

    m_mergedSeriesComboBox = new ComboBox();
    vLayout->addWidget(m_mergedSeriesComboBox);

    GroupBox* seriesBox = new GroupBox("Séries");
    m_seriesLayout = new QVBoxLayout();
    seriesBox->setLayout(m_seriesLayout);
    vLayout->addWidget(seriesBox);

    m_checkBoxesGroup.setExclusive(false); 

    PushButton* okButton = new PushButton("Ok");
    vLayout->addWidget(okButton);

    setLayout(vLayout);

    // Event connections
    connect(m_mergedSeriesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCheckboxes()));
    connect(&m_checkBoxesGroup, SIGNAL(buttonClicked(int)), this, SLOT(moveSeriesInterfaceIntoFusion(int)));
    connect(m_addMergedSeriesButton, SIGNAL(clicked()), this, SLOT(askNewFusion()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
}