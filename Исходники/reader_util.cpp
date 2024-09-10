std::string ReaderUtil::DetectEncoding(const std::string& database_file) {
	std::string encoding;
#ifdef LCF_SUPPORT_ICU
	std::ostringstream text;

	//Populate Data::terms or will empty by default even if load fails
	LDB_Reader::Load(database_file, "");

	text <<
	Data::terms.menu_save << " " <<
	Data::terms.menu_quit << " " <<
	Data::terms.new_game << " " <<
	Data::terms.load_game << " " <<
	Data::terms.exit_game << " " <<
	Data::terms.status << " " <<
	Data::terms.row << " " <<
	Data::terms.order << " " <<
	Data::terms.wait_on << " " <<
	Data::terms.wait_off << " " <<
	Data::terms.level << " " <<
	Data::terms.health_points << " " <<
	Data::terms.spirit_points << " " <<
	Data::terms.normal_status << " " <<
	Data::terms.exp_short << " " <<
	Data::terms.lvl_short << " " <<
	Data::terms.hp_short << " " <<
	Data::terms.sp_short << " " <<
	Data::terms.sp_cost << " " <<
	Data::terms.attack << " " <<
	Data::terms.defense << " " <<
	Data::terms.spirit << " " <<
	Data::terms.agility << " " <<
	Data::terms.weapon << " " <<
	Data::terms.shield << " " <<
	Data::terms.armor << " " <<
	Data::terms.helmet << " " <<
	Data::terms.accessory << " " <<
	Data::terms.save_game_message << " " <<
	Data::terms.load_game_message << " " <<
	Data::terms.file << " " <<
	Data::terms.exit_game_message << " " <<
	Data::terms.yes << " " <<
	Data::terms.no;

	// Checks if there are more than the above 33 spaces (no data)
	if (text.str().size() > 33)
	{
		UErrorCode status = U_ZERO_ERROR;
		UCharsetDetector* detector = ucsdet_open(&status);

		std::string s = text.str();
		ucsdet_setText(detector, s.c_str(), s.length(), &status);

		const UCharsetMatch* match = ucsdet_detect(detector, &status);
		if (match != NULL)
		{
			encoding = ucsdet_getName(match, &status);
		}
		ucsdet_close(detector);

		// Fixes to ensure proper Windows encodings
		if (encoding == "Shift_JIS")
		{
			encoding = "ibm-943_P130-1999"; // Japanese with Yen backslash
		}
		else if (encoding == "EUC-KR")
		{
			encoding = "ibm-949_P110-1999"; // Korean with Won backslash
		}
		else if (encoding == "ISO-8859-1" || encoding == "windows-1252")
		{
			encoding = "ibm-5348_P100-1997"; // Occidental with Euro
		}
		else if (encoding == "ISO-8859-2" || encoding == "windows-1250")
		{
			encoding = "ibm-5346_P100-1998"; // Central Europe with Euro
		}
		else if (encoding == "ISO-8859-5" || encoding == "windows-1251")
		{
			encoding = "ibm-5347_P100-1998"; // Cyrillic with Euro
		}
		else if (encoding == "ISO-8859-6" || encoding == "windows-1256")
		{
			encoding = "ibm-9448_X100-2005"; // Arabic with Euro + 8 chars
		}
		else if (encoding == "ISO-8859-7" || encoding == "windows-1253")
		{
			encoding = "ibm-5349_P100-1998"; // Greek with Euro
		}
		else if (encoding == "ISO-8859-8" || encoding == "windows-1255")
		{
			encoding = "ibm-9447_P100-2002"; // Hebrew with Euro
		}
	}
#endif

	return encoding;
}