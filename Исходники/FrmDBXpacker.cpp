void __fastcall TDB_packer::ExtBtn3Click(TObject *Sender)
{
	TElShellTreeItem* itm = shellTree->ItemFocused;
    if(!itm->IsFolder)
    {
        AnsiString str				= itm->FullName;
        int root_len 				= xr_strlen(m_root_folder);
        int len						= str.Length();
    	lbIncludeFiles->Items->Add( str.SubString(root_len+1,len-root_len) );
    }
}