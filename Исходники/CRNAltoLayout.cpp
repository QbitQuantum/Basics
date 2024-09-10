/*! \return	the quality of the original page */
Option<Alto::Layout::Page::Quality> Alto::Layout::Page::GetQuality() const
{
	Option<Quality> quality;
	StringUTF8 str = GetAttribute<StringUTF8>("QUALITY");
	if (str.IsNotEmpty())
	{
		str.ToLower();
		if (str == "OK")
			quality = Quality::Ok;
		else if (str == "Missing")
			quality = Quality::Missing;
		else if (str == "Missing in original")
			quality = Quality::MissingInOriginal;
		else if (str == "Damaged")
			quality = Quality::Damaged;
		else if (str == "Retained")
			quality = Quality::Retained;
		else if (str == "Target")
			quality = Quality::Target;
		else if (str == "As in original")
			quality = Quality::AsInOriginal;
	}
	return quality;
}