void SearchFilter::updateFilter() {
	mFilterRegExp.setPattern(mRegExp->currentText());
	mFilterRegExp.setCaseSensitivity(Qt::CaseInsensitive);
	if(! mFilterRegExp.isValid()) {
		QMessageBox::warning(this, tr("Warning - Museeq"), tr("Invalid regular expression, disabling it"));
		mFilterRegExp.setPattern(QString::null);
	}

	bool ok, neg = false;
	qint64 factor = 1;
	QString s = mSize->currentText();
	mFilterSizeExact = false;
	mFilterSize = 0;
	if(! s.isEmpty()) {
		if(s[0] == '=') {
			mFilterSizeExact = true;
			s = s.mid(1);
		} else if(s[0] == '<') {
			neg = true;
			s = s.mid(1);
		}

		if(! s.isEmpty()) {
			QString l = s.right(1).toLower();
			if(l == tr("k"))
				factor = 1024;
			else if(l == tr("m"))
				factor = 1024*1024;
			else if(l == tr("g"))
				factor = 1024*1024*1024;
			if(factor != 1)
				s = s.left(s.length() - 1);
		}

		mFilterSize = s.toInt(&ok);
		if(! ok) {
			QMessageBox::warning(this, tr("Warning - Museeq"), tr("Invalid size filter, disabling it"));
			mFilterSizeExact = false;
			mFilterSize = 0;
		} else {
			if(neg)
				mFilterSize *= -1;
			mFilterSize *= factor;
		}
	}

	neg = false;
	s = mBitrate->currentText();
	mFilterBitrateExact = false;
	mFilterBitrate = 0;
	if(! s.isEmpty()) {
		if(s[0] == '=') {
			mFilterBitrateExact = true;
			s = s.mid(1);
		} else if(s[0] == '<') {
			neg = true;
			s = s.mid(1);
		}
		mFilterBitrate = s.toInt(&ok);
		if(! ok) {
			QMessageBox::warning(this, tr("Warning - Museeq"), tr("Invalid bitrate filter, disabling it"));
			mFilterBitrateExact = false;
			mFilterBitrate = 0;
		} else if(neg)
			mFilterBitrate *= -1;
	}

	mFilterFreeSlot = mFreeSlot->isChecked();
                mFilterInvertMatch = mInvertMatch->isChecked();

	emit filterChanged();
}