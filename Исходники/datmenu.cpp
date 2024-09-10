ui_menu_dats_view::ui_menu_dats_view(running_machine &machine, render_container *container, const game_driver *driver) : ui_menu(machine, container)
{
	image_interface_iterator iter(machine.root_device());
	for (device_image_interface *image = iter.first(); image != nullptr; image = iter.next())
	{
		if (image->filename())
		{
			m_list = strensure(image->software_list_name());
			m_short = strensure(image->software_entry()->shortname());
			m_long = strensure(image->software_entry()->longname());
			m_parent = strensure(image->software_entry()->parentname());
		}
	}
	m_driver = (driver == nullptr) ? &machine.system() : driver;

	init_items();
}