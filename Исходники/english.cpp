String english_singular(const String& str) {
	if (str.size() > 3 && is_substr(str, str.size()-3, _("ies"))) {
		return str.substr(0, str.size() - 3) + _("y");
	} else if (str.size() > 3 && is_substr(str, str.size()-3, _("oes"))) {
		return str.substr(0, str.size() - 2);
	} else if (str.size() > 4 && is_substr(str, str.size()-4, _("ches"))) {
		return str.substr(0, str.size() - 2);
	} else if (str.size() > 4 && is_substr(str, str.size()-4, _("shes"))) {
		return str.substr(0, str.size() - 2);
	} else if (str.size() > 4 && is_substr(str, str.size()-4, _("sses"))) {
		return str.substr(0, str.size() - 2);
	} else if (str.size() > 5 && is_substr(str, str.size()-3, _("ves")) && (is_substr(str, str.size()-5, _("el")) || is_substr(str, str.size()-5, _("ar")) )) {
		return str.substr(0, str.size() - 3) + _("f");
	} else if (str.size() > 1 && str.GetChar(str.size() - 1) == _('s')) {
		return str.substr(0, str.size() - 1);
	} else if (str.size() >= 3 && is_substr(str, str.size()-3, _("men"))) {
		return str.substr(0, str.size() - 2) + _("an");
	} else {
		return str;
	}
}