// 给 QLineEdit 最右边创建一个按钮
QPushButton *UiUtil::createLineEditRightButton(QLineEdit *edit) {
    QPushButton *button = new QPushButton();
    QHBoxLayout *layout = new QHBoxLayout();
    button->setCursor(Qt::ArrowCursor);
    layout->addStretch();
    layout->addWidget(button);
    edit->setLayout(layout);
    UiUtil::setWidgetPaddingAndSpacing(edit, 0, 0);

    return button;
}