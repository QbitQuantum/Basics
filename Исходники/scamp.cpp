void CSCampaign::RefreshDate(int camp)
{
	CRButton*   s;
   	
	s=GETDLGITEM(IDC_RBUTTONDATE);
	s->SetString(LoadResString(IDS_L_SCAMPAIGNDATE1+camp));


}