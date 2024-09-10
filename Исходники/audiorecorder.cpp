AudioRecorder::AudioRecorder()
{
//! [create-objs-1]
    audiosource = new QAudioCaptureSource;
    capture = new QMediaRecorder(audiosource);
//! [create-objs-1]

    // set a default file
    capture->setOutputLocation(QUrl("test.raw"));

    QWidget *window = new QWidget;
    QGridLayout* layout = new QGridLayout;

    QLabel* deviceLabel = new QLabel;
    deviceLabel->setText("Devices");
    deviceBox = new QComboBox(this);
    deviceBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    QLabel* codecLabel = new QLabel;
    codecLabel->setText("Codecs");
    codecsBox = new QComboBox(this);
    codecsBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    QLabel* qualityLabel = new QLabel;
    qualityLabel->setText("Quality");
    qualityBox = new QComboBox(this);
    qualityBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

//! [device-list]
    for(int i = 0; i < audiosource->deviceCount(); i++)
        deviceBox->addItem(audiosource->name(i));
//! [device-list]

//! [codec-list]
    QStringList codecs = capture->supportedAudioCodecs();
    for(int i = 0; i < codecs.count(); i++)
        codecsBox->addItem(codecs.at(i));
//! [codec-list]

    qualityBox->addItem("Low");
    qualityBox->addItem("Medium");
    qualityBox->addItem("High");

    connect(capture, SIGNAL(durationChanged(qint64)), this, SLOT(updateProgress(qint64)));
    connect(capture, SIGNAL(stateChanged(QMediaRecorder::State)), this, SLOT(stateChanged(QMediaRecorder::State)));

    layout->addWidget(deviceLabel,0,0,Qt::AlignHCenter);
    connect(deviceBox,SIGNAL(activated(int)),SLOT(deviceChanged(int)));
    layout->addWidget(deviceBox,0,1,1,3,Qt::AlignLeft);

    layout->addWidget(codecLabel,1,0,Qt::AlignHCenter);
    connect(codecsBox,SIGNAL(activated(int)),SLOT(codecChanged(int)));
    layout->addWidget(codecsBox,1,1,Qt::AlignLeft);

    layout->addWidget(qualityLabel,1,2,Qt::AlignHCenter);
    connect(qualityBox,SIGNAL(activated(int)),SLOT(qualityChanged(int)));
    layout->addWidget(qualityBox,1,3,Qt::AlignLeft);

    fileButton = new QPushButton(this);
    fileButton->setText(tr("Output File"));
    connect(fileButton,SIGNAL(clicked()),SLOT(selectOutputFile()));
    layout->addWidget(fileButton,3,0,Qt::AlignHCenter);

    button = new QPushButton(this);
    button->setText(tr("Record"));
    connect(button,SIGNAL(clicked()),SLOT(toggleRecord()));
    layout->addWidget(button,3,3,Qt::AlignHCenter);

    recTime = new QLabel;
    recTime->setText("0 sec");
    layout->addWidget(recTime,4,0,Qt::AlignHCenter);

    window->setLayout(layout);
    setCentralWidget(window);
    window->show();

    active = false;
}