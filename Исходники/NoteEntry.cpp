bool NoteEntry::setFX(QChar fx)
{
	if(fx.isLetterOrNumber() || fx == '-')
	{
		// TODO: check if param match, if not reset to 00
		effect=fx.toUpper().toAscii();
		return true;
	}
	return false;
}