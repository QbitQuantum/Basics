void CSequenceEditor::OnReadReadwhiletyping() 
{
	readwhiletyping=(!readwhiletyping);

	CMenu* menu = GetSeqDocument()->pFrame->GetMenu( );
	
	
	if (readwhiletyping) menu->CheckMenuItem(ID_READ_READWHILETYPING,MF_CHECKED);
	else menu->CheckMenuItem(ID_READ_READWHILETYPING,MF_UNCHECKED); 


	
	
}