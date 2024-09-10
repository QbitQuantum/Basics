void RepRapSerial::SendNextLine()
{
	if ( com->errorStatus() ) 
	{
		m_bConnecting = false;
		m_bConnected = false;
		m_bPrinting = false;
		{
			ToolkitLock guard;
			gui->MVC->serialConnectionLost();
		}
		return;
	}
	if (m_bPrinting == false)
		return;
	if (m_iLineNr < buffer.size())
	{
		string a = buffer[m_iLineNr];
		SendData(a.c_str(), m_iLineNr++);
	}
	else	// we are done
	{
		ToolkitLock guard;

		m_bPrinting = false;
		buffer.clear();
		gui->ProgressBar->label("Print done");
		gui->MVC->PrintDone();
		return;
	}
	if (gui) {
		unsigned long time = Platform::getTickCount();
		if (startTime == 0)
			startTime = time;
		// it is just wasteful to update the GUI > once per sec.
		if (time - lastUpdateTime > 1000) {
			ToolkitLock guard;

			double elapsed = (time - startTime) / 1000.0;
			double max = gui->ProgressBar->maximum();
			double lines_per_sec = elapsed > 1 ? (double)m_iLineNr / elapsed : 1.0;
			double remaining = (double)(max - m_iLineNr) / lines_per_sec;

			/*
			 * Fltk has no way of knowing if this is a meaningful
			 * change, and has a habit of doing expensive re-draws.
			 * Detect whether there will be any visible change and
			 * if not, don't update.
			 */
			if (fabs (((double)m_iLineNr - gui->ProgressBar->value()) / max) > 1.0/1000.0)
				gui->ProgressBar->value ((float)m_iLineNr);

			int remaining_seconds = (int)fmod (remaining, 60.0);
			int remaining_minutes = ((int)fmod (remaining, 3600.0) - remaining_seconds) / 60;
			int remaining_hours = (int)remaining / 3600;

			std::stringstream oss;

			/*
			 * Trade accuracy for reduced UI update frequency.
			 */
			if (remaining_hours > 0)
				oss << setw(2) << remaining_hours << "h" << remaining_minutes << "m";
			else if (remaining_minutes > 5)
				oss << setw(2) << remaining_minutes << "m";
			else if (remaining_seconds > 0)
				oss << setw(2) << remaining_minutes << "m" << remaining_seconds << "s";
			else
				oss << "Progress";

			std::string s = oss.str();
			const char *old_label = gui->ProgressBar->label();
			if (!old_label || strcmp (old_label, s.c_str()))
				gui->ProgressBar->copy_label(s.c_str());
		}

	}

}