void MusicSongSearchOnlineWidget::createToolWidget()
{
    m_textLabel = new QLabel(this);
    m_textLabel->setGeometry(0, 0, 280, 30);
    m_textLabel->setTextFormat(Qt::RichText);
    m_textLabel->setText(tr("&nbsp;find no result"));

    QLabel *colorLabel = new QLabel(this);
    colorLabel->setStyleSheet(MusicUIObject::MCustomStyle17);
    colorLabel->setGeometry(0, 30, width(), 35);

    QCheckBox *label_checkBox = new QCheckBox(this);
    label_checkBox->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    label_checkBox->setGeometry(7, 40, 20, 20);
    connect(label_checkBox, SIGNAL(clicked(bool)), m_searchTableWidget,
                            SLOT(setSelectedAllItems(bool)));

    QLabel *Label1 = new QLabel(tr("Song"), this);
    Label1->setStyleSheet(MusicUIObject::MCustomStyle18);
    Label1->setGeometry(120, 40, 60, 20);
    QLabel *Label2 = new QLabel(tr("Artist"), this);
    Label2->setStyleSheet(MusicUIObject::MCustomStyle18);
    Label2->setGeometry(310, 40, 60, 20);
    QLabel *Label3 = new QLabel(tr("Operator"), this);
    Label3->setStyleSheet(MusicUIObject::MCustomStyle18);
    Label3->setGeometry(450, 40, 60, 20);

    m_playButton = new QPushButton(tr("Play"), this);
    m_playButton->setGeometry(315, 5, 70, 20);
    m_playButton->setStyleSheet(MusicUIObject::MPushButtonStyle05);
    m_playButton->setCursor(QCursor(Qt::PointingHandCursor));

    QPushButton *addButton = new QPushButton(tr("Add"), this);
    addButton->setGeometry(390, 5, 70, 20);
    addButton->setStyleSheet(MusicUIObject::MPushButtonStyle05);
    addButton->setCursor(QCursor(Qt::PointingHandCursor));

    QPushButton *downloadButton = new QPushButton(tr("Download"), this);
    downloadButton->setGeometry(465, 5, 70, 20);
    downloadButton->setStyleSheet(MusicUIObject::MPushButtonStyle05);
    downloadButton->setCursor(QCursor(Qt::PointingHandCursor));

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_playButton, 0);
    buttonGroup->addButton(addButton, 1);
    buttonGroup->addButton(downloadButton, 2);
    connect(buttonGroup, SIGNAL(buttonClicked(int)), SLOT(buttonClicked(int)));
}