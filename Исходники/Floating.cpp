string Floating::defaultCSSClass() const
{ 
	if (!defaultcssclass_.empty())
		return defaultcssclass_;
	string d;
	string n = floattype_;
	string::const_iterator it = n.begin();
	string::const_iterator en = n.end();
	for (; it != en; ++it) {
		if (!isAlphaASCII(*it))
			d += "_";
		else if (isLower(*it))
			d += *it;
		else
			d += support::lowercase(*it);
	}
	// are there other characters we need to remove?
	defaultcssclass_ = "float-" + d;
	return defaultcssclass_;
}