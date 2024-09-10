//---------------------------------------------------------------------------------------------------------------------
void ConfigDialog::createIcon(const QString &icon, const QString &text)
{
    QListWidgetItem *button = new QListWidgetItem(contentsWidget);
    button->setIcon(QIcon(icon));
    button->setText(text);
    button->setTextAlignment(Qt::AlignHCenter);
    button->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}