ChooseGeneralDialog::ChooseGeneralDialog(const QStringList &general_names, QWidget *parent)
    :QDialog(parent), free_chooser(NULL)
{
    setWindowTitle(tr("Choose general"));

    QList<const General *> generals;
    foreach(QString general_name, general_names){
        const General *general = Sanguosha->getGeneral(general_name);
        generals << general;
    }

    QSignalMapper *mapper = new QSignalMapper(this);
    QList<OptionButton *> buttons;
    QString category("card");
    QSize icon_size(200*0.8, 290*0.8);
    if(generals.length() > 10){
        category = "big";
        icon_size = QSize(94, 96);
    }

    foreach(const General *general, generals){
        QString icon_path = general->getPixmapPath(category);
        QString caption = Sanguosha->translate(general->objectName());
        OptionButton *button = new OptionButton(icon_path, caption);
        button->setToolTip(general->getSkillDescription());
        button->setIconSize(icon_size);
        buttons << button;

        mapper->setMapping(button, general->objectName());
        connect(button, SIGNAL(double_clicked()), mapper, SLOT(map()));
        connect(button, SIGNAL(double_clicked()), this, SLOT(accept()));

        // special case
        if(Self->getRoleEnum() == Player::Lord && general->objectName() == "shencaocao"){
            button->setEnabled(false);
        }
    }