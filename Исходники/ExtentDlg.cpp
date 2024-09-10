void ExtentDlg::FormatExtent(wxString &str, double value)
{
	if (m_bDMS)
	{
		bool sign = value > 0;
		value = fabs(value);
		int degrees = (int) value;
		value = (value - degrees) * 60;
		int minutes = (int) value;
		value = (value - minutes) * 60;
		double seconds = value;

		str.Printf(_T("%s%d %d %.2lf"), sign?"":"-", degrees, minutes, seconds);
	}
	else
		str.Printf(m_fs, value);
}