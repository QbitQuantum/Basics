void EditPanel::onTextColorClicked(bool /*checked*/)
{
	QColor color;
	GetTextColor(color);
	color = QColorDialog::getColor(color, this, tr("Text Color"));
	SetTextColor(color);
	emit edited();
}