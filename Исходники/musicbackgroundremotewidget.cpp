void MusicBackgroundRemoteWidget::createButton()
{
    for(int i=0; i<4; ++i)
    {
        QPushButton *button = new QPushButton(this);
        button->setFixedHeight(25);
        button->setText(tr("NetButton%1").arg(i + 1));
        button->setStyleSheet(MusicUIObject::MPushButtonStyle05);
        button->setCursor(QCursor(Qt::PointingHandCursor));
        m_group->addButton(button, i);
    }
    connect(m_group, SIGNAL(buttonClicked(int)), SLOT(buttonClicked(int)));
}