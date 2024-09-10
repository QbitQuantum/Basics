static void testStringMap()
{
	enum { numStrings = 1000 };

	HashMap<std::string, U32> map;
	std::vector<HashMapPair<std::string, U32>> pairs;

	srand(0);

	for(Uptr i = 0;i < numStrings;++i)
	{
		while(true)
		{
			std::string randomString = generateRandomString();

			bool alreadySawString = false;
			for(const HashMapPair<std::string, U32>& pair : pairs)
			{
				if(pair.key == randomString)
				{
					alreadySawString = true;
					break;
				}
			}

			if(!alreadySawString)
			{
				pairs.emplace_back(std::move(randomString), rand());
				break;
			}
		};
	}

	for(Uptr i = 0;i < pairs.size();++i)
	{
		errorUnless(map.add(pairs[i].key, pairs[i].value));
		errorUnless(!map.add(pairs[i].key, pairs[i].value));

		for(Uptr j = 0;j < pairs.size();++j)
		{
			const U32* valuePtr = map.get(pairs[j].key);
			if(j <= i)
			{
				errorUnless(valuePtr && *valuePtr == pairs[j].value);
			}
			else
			{
				errorUnless(!valuePtr);
			}
		}
	}

	for(Uptr i = 0;i < pairs.size();++i)
	{
		errorUnless(map.remove(pairs[i].key));
		errorUnless(!map.remove(pairs[i].key));

		for(Uptr j = 0;j < pairs.size();++j)
		{
			const U32* valuePtr = map.get(pairs[j].key);
			if(j > i)
			{
				errorUnless(valuePtr && *valuePtr == pairs[j].value);
			}
			else
			{
				errorUnless(!valuePtr);
			}
		}
	}
}