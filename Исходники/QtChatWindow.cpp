void QtChatWindow::beginCorrection() {
	boost::optional<AlertID> newCorrectingAlert;
	if (correctionEnabled_ == Maybe) {
		newCorrectingAlert = addAlert(Q2PSTRING(tr("This chat may not support message correction. If you send a correction anyway, it may appear as a duplicate message")));
	}
	else if (correctionEnabled_ == No) {
		newCorrectingAlert = addAlert(Q2PSTRING(tr("This chat does not support message correction.  If you send a correction anyway, it will appear as a duplicate message")));
	}

	if (newCorrectingAlert) {
		if (correctingAlert_) {
			removeAlert(*correctingAlert_);
		}
		correctingAlert_ = newCorrectingAlert;
	}

	QTextCursor cursor = input_->textCursor();
	cursor.select(QTextCursor::Document);
	cursor.beginEditBlock();
	cursor.insertText(QString(lastSentMessage_));
	cursor.endEditBlock();
	isCorrection_ = true;
	correctingLabel_->show();
	input_->setStyleSheet(alertStyleSheet_);
	labelsWidget_->setEnabled(false);
}