OMenu::~OMenu() {
	if (::IsMenu(m_hMenu)) {
		while(GetMenuItemCount() != 0)
			RemoveMenu(0, MF_BYPOSITION);
	} else {
		// How can we end up here??? it sure happens sometimes..
		for (OMenuItem::Iter i = items.begin(); i != items.end(); ++i) {
			delete *i;
		}
	}
	//pUnMap();
}