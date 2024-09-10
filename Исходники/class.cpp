void Class::SetName(ConstString name,bool badd2map)
{
	if(name.length())
	{
		mClassName = AddPooledString(name.c_str());

		if( badd2map )
		{
			ClassMapType::iterator it = mClassMap.find(mClassName);
			if(it != mClassMap.end())
			{
				if(it->second != this)
				{
					Class *previous = it->second;

					orkprintf("ERROR: Duplicate class name %s! previous class %p\n", mClassName.c_str(), previous);
					OrkAssert(false);
				}
			}
			else
			{
				mClassMap.AddSorted(mClassName, this);
			}
		}
	}
}