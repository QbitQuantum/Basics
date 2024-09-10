//---------------------------------------------------------------
// Purpose: 
//---------------------------------------------------------------
void CEntityOutputWnd::UpdateEventComboBox()
{
	CString oldText;
	m_cbEvt.GetWindowText(oldText);

	m_cbEvt.ResetContent();

	for(int id : m_list.GetEditIds()) //iterate over selected outputs
	{
		COutputListWnd::OutputSourceList *sourceList = m_list.GetSourceEnts(id);
		for(const std::pair<CEditorEntity*, CEntityOutput*> &outputPair : *sourceList) //iterate over output source entities
		{
			CEditorEntity *ent = outputPair.first;
			CEntityRegisterEntity *regEnt = GetEntityRegister()->GetEntity(ent->GetClassnameA());
			if(regEnt)
			{
				size_t numOuts = regEnt->GetNumOutputs();
				for(size_t i = 0; i < numOuts; i++) //iterate over the possible outputs of this source entity
				{
					const CEntityRegisterOutput *regOut = regEnt->GetOutput(i);
					CString outName(CA2T(regOut->name.c_str()));
					if( m_cbEvt.FindString(-1, outName) == CB_ERR )
						m_cbEvt.AddString(outName);
				}
			}				
		}
	}

	m_cbEvt.SetWindowText(oldText);
}