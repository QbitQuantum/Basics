void eTimeCorrectionEditWindow::yearChanged( eListBoxEntryText* )
{
	cmonth->setCurrent( (int) cmonth->getCurrent()->getKey(), true );
	setFocus(cyear);
}