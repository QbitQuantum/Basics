int SG_Grid_Cache_Check(CSG_Grid_System &m_System, int nValueBytes)
{
	if(	SG_Grid_Cache_Get_Automatic() && m_System.Get_NCells() * nValueBytes > SG_Grid_Cache_Get_Threshold() )
	{
		switch( SG_Grid_Cache_Get_Confirm() )
		{
		default:
			break;

		case 1:
			{
				CSG_String	s;

				s.Printf(SG_T("%s\n%s\n%s: %.2fMB"),
					LNG("Shall I activate file caching for new grid."),
					m_System.Get_Name(),
					LNG("Total memory size"),
					(m_System.Get_NCells() * nValueBytes) / (double)N_MEGABYTE_BYTES
				);

				if( SG_UI_Dlg_Continue(s, LNG("Activate Grid File Cache?")) )
				{
				//	Memory_Type	= GRID_MEMORY_Cache;

					return( SG_Grid_Cache_Get_Threshold() );
				}
			}
			break;

		case 2:
			{
				CSG_Parameters	p(NULL, LNG("Activate Grid File Cache?"), SG_T(""));

				p.Add_Value(
					NULL	, SG_T("BUFFERSIZE")	, LNG("Buffer Size [MB]"),
					SG_T(""),
					PARAMETER_TYPE_Double, SG_Grid_Cache_Get_Threshold_MB(), 0.0, true
				);

				if( SG_UI_Dlg_Parameters(&p, LNG("Activate Grid File Cache?")) )
				{
				//	Memory_Type	= GRID_MEMORY_Cache;

				//	Set_Buffer_Size((int)(p(SG_T("BUFFERSIZE"))->asDouble() * N_MEGABYTE_BYTES));

					return( (int)(p(SG_T("BUFFERSIZE"))->asDouble() * N_MEGABYTE_BYTES) );
				}
			}
			break;
		}
	}

	return( 0 );
}