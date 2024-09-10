void CCareer::OnTextChangedName(LPTSTR text) 
{
	trunc(text,PLAYERNAMELEN - 1);		
}