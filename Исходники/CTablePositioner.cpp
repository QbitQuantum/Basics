// To be called once after connection
void CTablePositioner::PositionMyWindow()
{		
	// Build list of poker tables (child windows)
	// Use the shared memory (auto-connector) for that. 
	HWNDs_of_child_windows	= p_sharedmem->GetDenseListOfConnectedPokerWindows();
	_number_of_tables		= p_sharedmem->SizeOfDenseListOfAttachedPokerWindows();

	if (_number_of_tables <= 0)
	{
		// Do nothing if there are 0 tables connected.
		// Actually an empty list of tables consists of only NULLs,
		// but if MicroSofts table-arranging functions see a NULL
		// they will arrange all windows at the desktop.
		// That's not what we want.
		return;
	}
	if (preferences.table_positioner_options() == k_position_tables_tiled)
	{
		write_log(preferences.debug_table_positioner(), "[CTablePositioner] PositionMyWindow() Going to tile %d windows...\n", _number_of_tables);
		PositionMyWindow(HWNDs_of_child_windows);
		// Tiling windows: http://msdn.microsoft.com/en-us/library/windows/desktop/ms633554(v=vs.85).aspx
		// Unfortunatelly this fucntion had 2 disadvantages:
		//   * it allows small overlaps
		//   * it resizes all full-screen-windows back to default
		// Therefore we use our own TileWindows-function now.
		/*
		TileWindows(
			NULL,				// Parent; NULL = whole desktop
			MDITILE_HORIZONTAL,	// How; either MDITILE_HORIZONTAL or MDITILE_VERTICAL
			NULL,				// Target area; NULL = parent window, here desktop
			_number_of_tables,
			HWNDs_of_child_windows);
		*/
	}
	else if (preferences.table_positioner_options() == k_position_tables_cascaded)
	{
		write_log(preferences.debug_table_positioner(), "[CTablePositioner] PositionMyWindow() Going to cascade %d windows...\n", _number_of_tables);
		// Cascading windows: http://msdn.microsoft.com/en-us/library/windows/desktop/ms632674(v=vs.85).aspx
		CascadeWindows(
			NULL,				// Parent; NULL = whole desktop
			NULL,				// How; NULL means: order specified in the lpKids array
			NULL,				// Target area; NULL = parent window, here desktop
			_number_of_tables,
			HWNDs_of_child_windows);
	}
	else
	{
		// preferences.table_positioner_options() == k_position_tables_never
		write_log(preferences.debug_table_positioner(), "[CTablePositioner] PositionMyWindow() Not doing anything because of preferences.\n");
	}
}