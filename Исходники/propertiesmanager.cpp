void PropertiesManager::createOnConditionProperties(OnConditionGraphicsItem *oci)
{
    QLabel *label = new QLabel("<b>Edit On Condition</b>");
    addRow(label);

    QLineEdit *maths = new QLineEdit();
    maths->installEventFilter(&eventFilterObject);
    maths->setText(oci->getTriggerMaths()->equation);
    connect(maths, SIGNAL(textChanged(QString)), oci, SLOT(setTriggerMaths(QString)));
    addRow(tr("&Maths:"), maths);
    addWidget(new QLabel(tr("<i>in physiological units</i>")));

    QStringList errs;
    oci->getTriggerMaths()->validateMathInLine(root->al.data(), &errs);

    // sort out errors
    QSettings settings;
    int num_errs = settings.beginReadArray("warnings");
    settings.endArray();

    if (num_errs != 0) {

        // show errors by changing lineedit colour
        QPalette p = maths->palette();
        p.setColor( QPalette::Normal, QPalette::Base, QColor(255, 200, 200) );
        maths->setPalette(p);

        // clear errors
        settings.remove("warnings");

    }
    if (num_errs == 0) {

        // show no errors by changing lineedit colour
        QPalette p = maths->palette();
        p.setColor( QPalette::Normal, QPalette::Base, QColor(255, 255, 255) );
        maths->setPalette(p);

        // clear errors
        settings.remove("warnings");
    }

    //edit Synapse regime??

    root->addItemsToolbar->addAction(root->actionAddStateAssignment);
    root->addItemsToolbar->addAction(root->actionAddEventOut);
    root->addItemsToolbar->addAction(root->actionAddImpulseOut);
    root->actionDeleteItems->setEnabled(true);
}