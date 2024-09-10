void
DownloadProgressView::_UpdateStatusText()
{
	fInfoView->SetText("");
	BString buffer;
	if (sShowSpeed && fBytesPerSecond != 0.0) {
		// Draw speed info
		char sizeBuffer[128];
		buffer = "(";
		// Get strings for current and expected size and remove the unit
		// from the current size string if it's the same as the expected
		// size unit.
		BString currentSize = string_for_size((double)fCurrentSize, sizeBuffer,
			sizeof(sizeBuffer));
		BString expectedSize = string_for_size((double)fExpectedSize, sizeBuffer,
			sizeof(sizeBuffer));
		int currentSizeUnitPos = currentSize.FindLast(' ');
		int expectedSizeUnitPos = expectedSize.FindLast(' ');
		if (currentSizeUnitPos >= 0 && expectedSizeUnitPos >= 0
			&& strcmp(currentSize.String() + currentSizeUnitPos,
				expectedSize.String() + expectedSizeUnitPos) == 0) {
			currentSize.Truncate(currentSizeUnitPos);
		}
		buffer << currentSize;
		buffer << " ";
		buffer << B_TRANSLATE_COMMENT("of", "...as in '12kB of 256kB'");
		buffer << " ";
		buffer << expectedSize;
		buffer << ", ";
		buffer << string_for_size(fBytesPerSecond, sizeBuffer,
			sizeof(sizeBuffer));
		buffer << B_TRANSLATE_COMMENT("/s)", "...as in 'per second'");
		float stringWidth = fInfoView->StringWidth(buffer.String());
		if (stringWidth < fInfoView->Bounds().Width())
			fInfoView->SetText(buffer.String());
		else {
			// complete string too wide, try with shorter version
			buffer << string_for_size(fBytesPerSecond, sizeBuffer,
				sizeof(sizeBuffer));
			buffer << B_TRANSLATE_COMMENT("/s)", "...as in 'per second'");
			stringWidth = fInfoView->StringWidth(buffer.String());
			if (stringWidth < fInfoView->Bounds().Width())
				fInfoView->SetText(buffer.String());
		}
	} else if (!sShowSpeed && fCurrentSize < fExpectedSize) {
		double totalBytesPerSecond = (double)(fCurrentSize
				- fEstimatedFinishReferenceSize)
			* 1000000LL / (system_time() - fEstimatedFinishReferenceTime);
		double secondsRemaining = (fExpectedSize - fCurrentSize)
			/ totalBytesPerSecond;
		time_t now = (time_t)real_time_clock();
		time_t finishTime = (time_t)(now + secondsRemaining);

		tm _time;
		tm* time = localtime_r(&finishTime, &_time);
		int32 year = time->tm_year + 1900;

		char timeText[32];
		time_t secondsPerDay = 24 * 60 * 60;
		// TODO: Localization of time string...
		if (now < finishTime - secondsPerDay) {
			// process is going to take more than a day!
			sprintf(timeText, "%0*d:%0*d %0*d/%0*d/%ld",
				2, time->tm_hour, 2, time->tm_min,
				2, time->tm_mon + 1, 2, time->tm_mday, year);
		} else {
			sprintf(timeText, "%0*d:%0*d",
				2, time->tm_hour, 2, time->tm_min);
		}

		BString buffer1(B_TRANSLATE_COMMENT("Finish: ", "Finishing time"));
		buffer1 << timeText;
		finishTime -= now;
		time = gmtime(&finishTime);

		BString buffer2;
		if (finishTime > secondsPerDay) {
			int64 days = finishTime / secondsPerDay;
			if (days == 1)
				buffer2 << B_TRANSLATE("Over 1 day left");
			else {
				buffer2 << B_TRANSLATE("Over %days days left");
				buffer2.ReplaceFirst("%days", BString() << days);
			}
		} else if (finishTime > 60 * 60) {
			int64 hours = finishTime / (60 * 60);
			if (hours == 1)
				buffer2 << B_TRANSLATE("Over 1 hour left");
			else {
				buffer2 << B_TRANSLATE("Over %hours hours left");
				buffer2.ReplaceFirst("%hours", BString() << hours);
			}
		} else if (finishTime > 60) {
			int64 minutes = finishTime / 60;
			if (minutes == 1)
				buffer2 << B_TRANSLATE("Over 1 minute left");
			else {
				buffer2 << B_TRANSLATE("%minutes minutes");
				buffer2.ReplaceFirst("%minutes", BString() << minutes);
			}
		} else {
			if (finishTime == 1)
				buffer2 << B_TRANSLATE("1 second left");
			else {
				buffer2 << B_TRANSLATE("%seconds seconds left");
				buffer2.ReplaceFirst("%seconds", BString() << finishTime);
			}
		}

		buffer = "(";
		buffer << buffer1 << " - " << buffer2 << ")";

		float stringWidth = fInfoView->StringWidth(buffer.String());
		if (stringWidth < fInfoView->Bounds().Width())
			fInfoView->SetText(buffer.String());
		else {
			// complete string too wide, try with shorter version
			buffer = "(";
			buffer << buffer1 << ")";
			stringWidth = fInfoView->StringWidth(buffer.String());
			if (stringWidth < fInfoView->Bounds().Width())
				fInfoView->SetText(buffer.String());
		}
	}
}