// method that seds pressed char to widget with focus
void ChumbyVirtualKeyboard::sendChar ( int indexOfCharToSend )
{
	pressTimer->stop();

	if ( verticalLayoutWidget2->isVisible() )  // when using "other" characters, leave method here
	{
		return;
	}

	QChar charToSend ( button[indexOfCharToSend]->text().at ( 0 ) );

	if ( !buttonC1->isChecked() && buttonC3->text() == QString ( ".?123" ) ) {
		QApplication::sendEvent ( parentWidget->focusWidget(), new QKeyEvent ( QEvent::KeyPress, charToSend.toLower().unicode(), Qt::NoModifier, QString ( charToSend.toLower() ) ) );
	} else {
		QApplication::sendEvent ( parentWidget->focusWidget(), new QKeyEvent ( QEvent::KeyPress, charToSend.unicode(), Qt::NoModifier, QString ( charToSend ) ) );
	}


	labelDisplayChar->hide();
	return;
}