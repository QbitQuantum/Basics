preferenceDialog::preferenceDialog(QWidget *parent,QSettings *settings) :
    QDialog(parent),
    ui(new Ui::preferenceDialog)
{
    _settings=settings;
    AudioDriverLst.clear();
    apply=false;
    resetsc=false;

    ui->setupUi(this);
    ui-> groupBox_17->setVisible(false);
#ifdef Q_OS_WIN
    if (DirectSoundEnumerateA(DirectSoundEnum, NULL) != DS_OK){
        qDebug( "Error: can't list the audio devices\n");


    }

    for (int i=0;i<AudioDriverLst.count();i++)
    {
        ui->cmbAO->addItem(AudioDriverLst.at(i));

    }
    ui->comboBoxStyle->addItem("windowsxp");
#endif


#ifdef Q_OS_LINUX
    ui->comboBox->setEnabled(false);
    ui->comboBoxStyle->addItem("GTK+");
#endif

    ui->stackedWidget->setCurrentIndex(0);
    on_listWidget_currentRowChanged(0);
    //Init sub encodings combo
    QStringList lstEncodings=QStringList(Languages::encodings().values());
    lstEncodings.sort();
    ui->comboBoxSubEncoding->addItems( lstEncodings);
    ui->labelVersion->setText("<span style=\" font-size:12pt; font-weight:600; color:#000000;\">ExMplayer v"+Version::stable()+ " Beta<span>");


}