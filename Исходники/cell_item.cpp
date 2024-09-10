void CellItem::setChar(QChar c) {
	if (c.isLetter())
	{
		is_empty = false;
		this->c = c.toUpper();
		update();
	}
}