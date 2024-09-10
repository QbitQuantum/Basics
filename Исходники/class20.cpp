void Class20::on_pushButton_clicked()
{
	//ui.listWidget->currentItem()->setText("Busy Boy");
	QListWidgetItem *itm = ui.listWidget->currentItem();
	itm->setText("Busy Boy");
	itm->setTextColor(Qt::red);
	itm->setBackgroundColor(Qt::black);
}