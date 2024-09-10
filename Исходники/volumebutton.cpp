VolumeButton::VolumeButton(QWidget *parent) :
    QToolButton(parent), menu(0), label(0), slider(0)
{
    setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    setPopupMode(QToolButton::InstantPopup);

    QWidget *popup = new QWidget(this);

    slider = new QSlider(Qt::Horizontal, popup);
    slider->setRange(0, 100);
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int)));

    label = new QLabel(popup);
    label->setAlignment(Qt::AlignCenter);
    label->setNum(100);
    label->setMinimumWidth(label->sizeHint().width());
    connect(slider, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));

    QBoxLayout *popupLayout = new QHBoxLayout(popup);
    popupLayout->setMargin(2);
    popupLayout->addWidget(slider);
    popupLayout->addWidget(label);

    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);

    stylize();
}