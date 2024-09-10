	void cImageManager::DeleteAllBitmapFrames()
	{
		FlushAll();
		for(tFrameBitmapListIt it=mlstBitmapFrames.begin();it!=mlstBitmapFrames.end();)
		{
			hplDelete(*it);
			it = mlstBitmapFrames.erase(it);
		}
	}