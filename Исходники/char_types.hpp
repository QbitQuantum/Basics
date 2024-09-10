	///
	/// Converts the wide character @p c to lowercase, returning the result
	/// @param c the character to convert to lowercase
	///
	inline wchar wchar_to_lower(wchar c){
		return (wchar) towlower(c);
	}