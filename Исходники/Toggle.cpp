void Toggle::connectWidget(Gtk::Widget* widget)
{
	if (dynamic_cast<Gtk::ToggleToolButton*>(widget) != NULL)
	{
		Gtk::ToggleToolButton* toolButton = static_cast<Gtk::ToggleToolButton*>(widget);

		toolButton->set_active(_toggled);

		// Connect the toggleToolbutton to the callback of this class
		_toggleWidgets[widget] = toolButton->signal_toggled().connect(
			sigc::mem_fun(*this, &Toggle::onToggleToolButtonClicked));
	}
	else if (dynamic_cast<Gtk::ToggleButton*>(widget) != NULL)
	{
		Gtk::ToggleButton* toggleButton = static_cast<Gtk::ToggleButton*>(widget);

		toggleButton->set_active(_toggled);

		// Connect the togglebutton to the callback of this class
		_toggleWidgets[widget] = toggleButton->signal_toggled().connect(
			sigc::mem_fun(*this, &Toggle::onToggleButtonClicked));
	}
	else if (dynamic_cast<Gtk::CheckMenuItem*>(widget) != NULL)
	{
		Gtk::CheckMenuItem* menuItem = static_cast<Gtk::CheckMenuItem*>(widget);

		menuItem->set_active(_toggled);

		// Connect the togglebutton to the callback of this class
		_toggleWidgets[widget] = menuItem->signal_toggled().connect(
			sigc::mem_fun(*this, &Toggle::onCheckMenuItemClicked));
	}
}