QPushButton* MusicVideoControl::createBarrageColorButton(int index)
{
    QPushButton *button = new QPushButton(this);
    switch(index)
    {
        case 1: button->setIcon(QIcon(":/color/white")); break;
        case 2: button->setIcon(QIcon(":/color/red")); break;
        case 3: button->setIcon(QIcon(":/color/orange")); break;
        case 4: button->setIcon(QIcon(":/color/yellow")); break;
        case 5: button->setIcon(QIcon(":/color/green")); break;
        case 6: button->setIcon(QIcon(":/color/blue")); break;
        case 7: button->setIcon(QIcon(":/color/purple")); break;
        case 8: button->setIcon(QIcon(":/color/black")); break;
    }
    button->setFixedSize(15, 15);
    button->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    button->setCursor(QCursor(Qt::PointingHandCursor));
    return button;
}