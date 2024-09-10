int CALLBACK ListSortProc( LPARAM lp1, LPARAM lp2, LPARAM lp3)
{
	int i ;
	if( lp3 == 0)
	{
		string s1 = ( (Mp3File*)lp1)->GetSaveName() ;
		string s2 = ( (Mp3File*)lp2)->GetSaveName() ;
		i = _mbscmp( (const unsigned char*)s1.c_str(), (const unsigned char*)s2.c_str()) ;
	}
	else if( lp3 == 1)
	{
		string s1 = ( (Mp3File*)lp1)->GetFilePath() ;
		string s2 = ( (Mp3File*)lp2)->GetFilePath() ;
		i = _mbscmp( (const unsigned char*)s1.c_str(), (const unsigned char*)s2.c_str()) ;
	}
	else if( lp3 == 2)
	{
		string s1 = ( (Mp3File*)lp1)->GetFileName() ;
		string s2 = ( (Mp3File*)lp2)->GetFileName() ;
		i = _mbscmp( (const unsigned char*)s1.c_str(), (const unsigned char*)s2.c_str()) ;
	}
	return i ;
}