/******************************************************************************
* Fetch the entered date/time.
* If 'checkExpired' is true and the entered value <= current time, an error occurs.
* If 'minsFromNow' is non-null, it is set to the number of minutes' delay selected,
* or to zero if a date/time was entered.
* In this case, if 'showErrorMessage' is true, output an error message.
* 'errorWidget' if non-null, is set to point to the widget containing the error.
* Reply = invalid date/time if error.
*/
KDateTime AlarmTimeWidget::getDateTime(int* minsFromNow, bool checkExpired, bool showErrorMessage, QWidget** errorWidget) const
{
	if (minsFromNow)
		*minsFromNow = 0;
	if (errorWidget)
		*errorWidget = 0;
	KDateTime now = KDateTime::currentUtcDateTime();
	now.setTime(QTime(now.time().hour(), now.time().minute(), 0));
	if (!mAtTimeRadio->isChecked())
	{
		if (!mDelayTimeEdit->isValid())
		{
			if (showErrorMessage)
				KMessageBox::sorry(const_cast<AlarmTimeWidget*>(this), i18nc("@info", "Invalid time"));
			if (errorWidget)
				*errorWidget = mDelayTimeEdit;
			return KDateTime();
		}
		int delayMins = mDelayTimeEdit->value();
		if (minsFromNow)
			*minsFromNow = delayMins;
		return now.addSecs(delayMins * 60).toTimeSpec(mTimeSpec);
	}
	else
	{
		bool dateOnly = mAnyTimeAllowed && mAnyTimeCheckBox && mAnyTimeCheckBox->isChecked();
		if (!mDateEdit->isValid()  ||  !mTimeEdit->isValid())
		{
			// The date and/or time is invalid
			if (!mDateEdit->isValid())
			{
				if (showErrorMessage)
					KMessageBox::sorry(const_cast<AlarmTimeWidget*>(this), i18nc("@info", "Invalid date"));
				if (errorWidget)
					*errorWidget = mDateEdit;
			}
			else
			{
				if (showErrorMessage)
					KMessageBox::sorry(const_cast<AlarmTimeWidget*>(this), i18nc("@info", "Invalid time"));
				if (errorWidget)
					*errorWidget = mTimeEdit;
			}
			return KDateTime();
		}

		KDateTime result;
		if (dateOnly)
		{
			result = KDateTime(mDateEdit->date(), mTimeSpec);
			if (checkExpired  &&  result.date() < now.date())
			{
				if (showErrorMessage)
					KMessageBox::sorry(const_cast<AlarmTimeWidget*>(this), i18nc("@info", "Alarm date has already expired"));
				if (errorWidget)
					*errorWidget = mDateEdit;
				return KDateTime();
			}
		}
		else
		{
			result = KDateTime(mDateEdit->date(), mTimeEdit->time(), mTimeSpec);
			if (checkExpired  &&  result <= now.addSecs(1))
			{
				if (showErrorMessage)
					KMessageBox::sorry(const_cast<AlarmTimeWidget*>(this), i18nc("@info", "Alarm time has already expired"));
				if (errorWidget)
					*errorWidget = mTimeEdit;
				return KDateTime();
			}
		}
		return result;
	}
}