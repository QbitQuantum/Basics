void wing_editor::OnSelchangeDepartureLocation() 
{
	CComboBox *box;

	box = (CComboBox *)GetDlgItem(IDC_DEPARTURE_TARGET);
	UpdateData();
	if (m_departure_location) {
		GetDlgItem(IDC_DEPARTURE_TARGET)->EnableWindow(TRUE);
		if (m_departure_target < 0) {
			m_departure_target = 0;
		}
		// we need to build up the list box content based on the departure type.  When
		// from a docking bay, only show ships in the list which have them.  Show all ships otherwise
		if ( m_departure_location == DEPART_AT_DOCK_BAY ) {
			management_add_ships_to_combo( box, SHIPS_2_COMBO_DOCKING_BAY_ONLY );
		} else {
			// I think that this section is currently illegal
			Int3();
		}
	} else {
		box->ResetContent();
		box->EnableWindow(TRUE);
		if ( m_departure_target < 0 )
			m_departure_target = -1;
		m_departure_target = 0;
		box->AddString("None");
		for (int i=0; i<Num_jump_nodes; i++)  
			box->AddString(Jumppoint_lists[i].name);
		//GetDlgItem(IDC_DEPARTURE_TARGET)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}