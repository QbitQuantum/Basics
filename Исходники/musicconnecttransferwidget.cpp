void MusicConnectTransferWidget::initColumns()
{
    MusicSongsList songs;
    QStringList names;
    emit getMusicLists(songs, names);

    QButtonGroup *group = new QButtonGroup(this);
    connect(group, SIGNAL(buttonClicked(int)), SLOT(currentPlayListSelected(int)));
    for(int i=0; i<songs.count(); ++i)
    {
        QPushButton *button = new QPushButton(QString("%1(%2)")
                                              .arg(names[i]).arg(songs[i].count()), this);
        button->setStyleSheet(MusicUIObject::MPushButtonStyle08);
        button->setCursor(QCursor(Qt::PointingHandCursor));
        button->setGeometry(32, 100 + 50*i, 90, 25);
        group->addButton(button, i);
    }

    QString path = M_SETTING->value(MusicSettingManager::MobileDevicePathChoiced).toString();
    ui->textLabel->setText(QString("( %1 )").arg(path));
    ui->transferButton->setEnabled( !path.isEmpty() );
}