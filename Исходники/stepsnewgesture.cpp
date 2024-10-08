StepsNewGesture::StepsNewGesture(ExecutionManager *pExecutionManager, int pNumberOfGesture, QWidget *parent)
{
    int labelFontSize = 23;
    QColor labelColor = QColor(210,210,210);

    this->executionManager = pExecutionManager;
    this->commandChooser = new CommandChooser(parent);

    this->stepper = new StepperNewGesture(this->executionManager, this->commandChooser, pNumberOfGesture, parent);

    /* Local */
    QString locale = QLocale::system().name().section('_', 0, 0);
    XmlConf* conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf != NULL)
    {
        if (conf->language != NULL)
        {
            locale = conf->language;
        }
    }
    if (locale.compare("en") != 0 && locale.compare("fr") != 0)
    {
        locale = "en";
    }

    /* STEP 0 */
    QWidget *step = new QWidget(stepper);
    QVBoxLayout* vLayoutStep = new QVBoxLayout(step);
    vLayoutStep->setMargin(0);
    Label* lblStepTop = new Label(tr("\n\nThe recording of a gesture MUST start and end with a neutral stance.\n\n"),step);
    lblStepTop->setTextColor(labelColor);
    lblStepTop->changeFontSize(16);
    lblStepTop->setPaintShadow(false);
    lblStepTop->setFixedHeight(60);
    lblStepTop->setPaintShadow(false);
    QLabel *picNeutral = new QLabel(step);
    QPixmap pix = QPixmap(Utils::getResourcesDirectory() + "/tuto/neutral_" + locale + ".png");
    picNeutral->setPixmap(pix);
    vLayoutStep->addWidget(lblStepTop);
    vLayoutStep->addWidget(picNeutral);
    stepper->addStep(tr("Information"),true,false,true, StepperNewGesture::First ,step);

    /* STEP 1 */
    Label *step1 = new Label(tr("You will have 5 seconds to place\nbefore registering your gesture\n1/") + QString::number(pNumberOfGesture),stepper);
    step1->changeFontSize(labelFontSize);
    step1->setTextColor(labelColor);
    step1->setPaintShadow(false);
    stepper->addStep(tr("Add a new gesture"),true,true,true, StepperNewGesture::StartTimer ,step1);

    /* STEP 2 */
    Label *step2 = new Label(tr("Ready ?"),stepper);
    step2->changeFontSize(labelFontSize);
    step2->setTextColor(labelColor);
    step2->setPaintShadow(false);
    stepper->addStep(tr("Add a new gesture"),false,true,true,StepperNewGesture::StartRecording ,step2);

    /* STEP 3 */
    QWidget* step3 = new QWidget(parent);
    QVBoxLayout* vLayoutStep3 = new QVBoxLayout(step3);
    GlView* glViewStep3= new GlView(step3);
    DAOLayer* dao = DAOLayer::getInstance();
    connect(dao, SIGNAL(skeletonDataReceived(QString)), glViewStep3,SLOT(skeletonDataReceived(QString)));
    Label* labelStep3 = new Label(tr("Realtime visualizer"), step3);
    labelStep3->setFixedHeight(50);
    labelStep3->changeFontSize(labelFontSize);
    labelStep3->setTextColor(labelColor);
    labelStep3->setPaintShadow(false);
    vLayoutStep3->addWidget(labelStep3);
    vLayoutStep3->addWidget(glViewStep3);
    glViewStep3->startAnimating();
    stepper->addStep(tr("Add a new gesture"),false,true,true,StepperNewGesture::VisualizeRecording ,step3);

    /* STEP 4 */
    QWidget* step4 = new QWidget(parent);
    QVBoxLayout* vLayoutStep4 = new QVBoxLayout(step4);
    this->glViewStep4= new GlView(step4);
    connect(this->executionManager, SIGNAL(gestureRecorded(Gesture*)), this, SLOT(gestureReceived(Gesture*)));
    Label *labelStep4 = new Label(tr("Is it the right gesture ?"),stepper);
    labelStep4->setFixedHeight(50);
    labelStep4->changeFontSize(labelFontSize);
    labelStep4->setTextColor(labelColor);
    labelStep4->setPaintShadow(false);
    vLayoutStep4->addWidget(labelStep4);
    vLayoutStep4->addWidget(this->glViewStep4);
    this->glViewStep4->startAnimating();
    stepper->addStep(tr("Add a new gesture"),true,true,true,StepperNewGesture::ConfigureAction,step4);

    /* STEP 5 */
    QWidget* step5 = new QWidget(parent);
    QVBoxLayout* vLayout = new QVBoxLayout(step5);


    QWidget* step5Bottom = new QWidget(step5);
    QHBoxLayout* hLayoutStep5 = new QHBoxLayout(step5Bottom);
    this->commandChooser->setParent(step5Bottom);

    ComboBox *combo = this->commandChooser->getCommandComboBox();
    KeyListener *keyListener = this->commandChooser->getCommandKeyListener();
    TextField *tfNewGesture = this->commandChooser->getCommandTextField();
    ButtonElement *btnCommand = this->commandChooser->getCommandButton();
    Label* labelRecordName = new Label("Record name : ",step5);
    labelRecordName->setPaintShadow(false);
    labelRecordName->setTextColor(labelColor);
    TextField *tfRecordName = this->commandChooser->getRecordNameTextField();


    hLayoutStep5->addWidget(combo);
    hLayoutStep5->addWidget(keyListener);
    hLayoutStep5->addWidget(tfNewGesture);
    hLayoutStep5->addWidget(btnCommand);
    hLayoutStep5->addWidget(labelRecordName);
    hLayoutStep5->addWidget(tfRecordName);

    Label *labelStep5 = new Label(tr("Command linked to your gesture"),step5);
    labelStep5->setPaintShadow(false);
    labelStep5->changeFontSize(labelFontSize);
    labelStep5->setTextColor(labelColor);
    labelStep5->setFixedHeight(50);

    vLayout->addWidget(labelStep5);
    vLayout->addWidget(step5Bottom);

    stepper->addStep(tr("Add a new gesture"),true,false,true,StepperNewGesture::SaveRecord,step5);

    /* STEP 6 */
    QWidget* step6 = new QWidget(parent);
    QLabel* labelLoading = new QLabel(step6);
    QMovie* loading = new QMovie(Utils::getResourcesDirectory() + "loader.gif", QByteArray(), labelLoading);
    labelLoading->resize(128, 128);
    labelLoading->setMovie(loading);
    loading->start();
    stepper->addStep(tr("Add a new gesture"),false,false,false,StepperNewGesture::Close,step6);
    labelLoading->move(step6->width()/2 - labelLoading->width()/2, step6->height()/2 - labelLoading->height()/2);
}