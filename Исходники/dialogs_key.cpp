not_null<Entry*> Key::entry() const {
	if (const auto p = base::get_if<not_null<History*>>(&_value)) {
		return *p;
	} else if (const auto p = base::get_if<not_null<Folder*>>(&_value)) {
		return *p;
	}
	Unexpected("Empty Dialogs::Key in Key::entry().");
}