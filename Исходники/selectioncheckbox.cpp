SelectionCheckBox::SelectionCheckBox(Container * parent) :
        CustomControl(parent)
{
    // The title is stored in the custom control so that we can present which olive
    // has been added or removed from the mix. So we initialize the title to an empty QString.
    mTitle = QString("");

    // A colored rectangle representing the olive color and the
    // CheckBox is aligned to the Right side of the component.
    Container *checkBoxContainer = Container::create().top(43.0f).bottom(43.0f);

    StackLayout *checkBoxLayout = new StackLayout();
    checkBoxLayout->setOrientation(LayoutOrientation::LeftToRight);
    checkBoxContainer->setLayout(checkBoxLayout);

    mColorContainer = new Container();
    mColorContainer->setBackground(Color::Black);
    mColorContainer->setPreferredSize(42, 42);
    mColorContainer->setRightMargin(33.0f);
    mColorContainer->setVerticalAlignment(VerticalAlignment::Center);

    // The CheckBox which will tell if the olive should be part of the
    // olive mix or not.
    mOliveCheckBox = new CheckBox();
    mOliveCheckBox->setObjectName("checkBox");
    mOliveCheckBox->setLayoutProperties(StackLayoutProperties::create().spaceQuota(1));

    connect(mOliveCheckBox, SIGNAL(checkedChanged(bool)), this,
            SLOT(onCheckedChanged(bool)));

    checkBoxContainer->add(mOliveCheckBox);
    checkBoxContainer->add(mColorContainer);

    setRoot(checkBoxContainer);
}