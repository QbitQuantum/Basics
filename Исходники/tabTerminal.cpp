void TabTerminal::_clearLine()
{
	QTextCursor c = this->textCursor();
	c.select(QTextCursor::LineUnderCursor);
	c.removeSelectedText();
	this->insertHtml(_userPrompt);
}