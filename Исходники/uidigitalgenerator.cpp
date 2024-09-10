/*!
    Constructs the UiDigitalGenerator with the given \a parent.
*/
UiDigitalGenerator::UiDigitalGenerator(DigitalSignals* digitalSignals,
                                       QWidget *parent) :
    QWidget(parent)
{
    int defaultStates = 32;
    mSignals = digitalSignals;

    GeneratorDevice* device = DeviceManager::instance().activeDevice()
            ->generatorDevice();
    if (device != NULL) {
        defaultStates = device->maxNumDigitalStates();
    }

    // Deallocation: ownership changed when calling setLayout
    QVBoxLayout* verticalLayout = new QVBoxLayout();

    mTable = createTable();

    verticalLayout->addWidget(createToolBar());
    verticalLayout->addWidget(mTable);

    setLayout(verticalLayout);


    setNumStates(defaultStates);
}