QWizardPage * MobileConnectionWizard::createIntroPage()
{
    QWizardPage *page = new QWizardPage();
    page->setTitle(i18nc("Mobile Connection Wizard", "Set up a Mobile Broadband Connection"));
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel(i18nc("Mobile Connection Wizard", "This assistant helps you easily set up a mobile broadband connection to a cellular (3G) network."));
    label->setWordWrap(true);
    layout->addWidget(label);

    label = new QLabel("\n" + i18nc("Mobile Connection Wizard", "You will need the following information:"));
    layout->addWidget(label);

    label = new QLabel(QString("  . %1\n  . %2\n  . %3").
                       arg(i18nc("Mobile Connection Wizard", "Your broadband provider's name")).
                       arg(i18nc("Mobile Connection Wizard", "Your broadband billing plan name")).
                       arg(i18nc("Mobile Connection Wizard", "(in some cases) Your broadband billing plan APN (Access Point Name)")));
    layout->addWidget(label);

    if (!mInitialMethodType) {
        label = new QLabel("\n" + i18nc("Mobile Connection Wizard", "Create a connection for &this mobile broadband device:"));
        layout->addWidget(label);

        mDeviceComboBox = new QComboBox();
        mDeviceComboBox->addItem(i18nc("Mobile Connection Wizard", "Any GSM device"));
        mDeviceComboBox->setItemData(0, Knm::Connection::Gsm);
        mDeviceComboBox->addItem(i18nc("Mobile Connection Wizard", "Any CDMA device"));
        mDeviceComboBox->setItemData(1, Knm::Connection::Cdma);
        mDeviceComboBox->insertSeparator(NUMBER_OF_STATIC_ENTRIES-1);
        label->setBuddy(mDeviceComboBox);
        layout->addWidget(mDeviceComboBox);

        QObject::connect(Solid::Control::NetworkManagerNm09::notifier(), SIGNAL(networkInterfaceAdded(QString)),
                         this, SLOT(introDeviceAdded(QString)));
        QObject::connect(Solid::Control::NetworkManagerNm09::notifier(), SIGNAL(networkInterfaceRemoved(QString)),
                         this, SLOT(introDeviceRemoved(QString)));
        QObject::connect(Solid::Control::NetworkManagerNm09::notifier(), SIGNAL(statusChanged(Solid::Networking::Status)),
                         this, SLOT(introStatusChanged(Solid::Networking::Status)));

        introAddInitialDevices();
    }

    page->setLayout(layout);

    return page;
}