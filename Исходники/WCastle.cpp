void CastleGame::seeker(char *sstring)
{
	rewind(fptr);
	while(fseeker(sstring) != FSUCCESS){}
}