void ConfigureInput::handleClick() {
    QPushButton* sender = qobject_cast<QPushButton*>(QObject::sender());
    previous_mapping = sender->text();
    sender->setText(tr("[waiting]"));
    sender->setFocus();
    grabKeyboard();
    grabMouse();
    changing_button = sender;
    timer->start(5000); // Cancel after 5 seconds
}