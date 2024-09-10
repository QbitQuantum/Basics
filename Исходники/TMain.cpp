//---------------------------------------------------------------------------
void TMain::ColorLog(UnicodeString token)
{
	int pos = 0;
	int foundAt = m_log->FindText(token,pos,m_log->Text.Length(),TSearchTypes());

	while(foundAt!=-1)
	{
		m_log->SelStart = foundAt;
		m_log->SelLength = token.Length();
		m_log->SelAttributes->Color = (TColor)0x00FF0080;

		pos = foundAt + token.Length();
		foundAt = m_log->FindText(token,pos,m_log->Text.Length(),TSearchTypes());
	}
	m_log->SelStart = m_log->Text.Length();
}