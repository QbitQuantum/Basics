/**
 * @brief Show a message box with a `message` and a `title`.
 * @param title  Title of the message box to be displayed.
 * @param message  Message in the message box.
 */
void QDialogUI::set_message(QString title, QString message)
{
    ui->FunctionsBox->setTitle(QApplication::translate("Util", title.toStdString().c_str()));
    ui->Functionlist->clear();
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(message);
    item->setFlags(Qt::ItemIsEnabled);
    ui->Functionlist->addItem(item);
}