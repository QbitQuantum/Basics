void CFindOptions::RemoveStartDir( const DString &startDir )
{
	DString _lowercase = startDir.ToLower();

	for(auto _it = mStartDirVec.begin();_it<mStartDirVec.end();_it++)
	{
		if(_lowercase.compare(_it->ToLower()) == 0) 
		{
			mStartDirVec.erase(_it);
			return;
		}
	}
}