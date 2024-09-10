	void LFListBase::push(void *element)
	{
		void *elementNext = (void*)((std::size_t)element + _nextPtrPadding);

		while (true)
		{
			Data datas;
			while (true)
			{
				datas = _datas;
				__int64 cr[2];
				cr[0] = (__int64)datas.size; /* low */
				cr[1] = (__int64)datas.head; /* high */
				if (_InterlockedCompareExchange128(&_datas.size, (__int64)datas.head, datas.size, &cr[0]) == 1)
				{
					break;
				}
			}
			Data oldDatas = datas;

			*(std::size_t*)(elementNext) = (std::size_t)datas.head;
			AGE_ASSERT((std::size_t)(elementNext) % 8 == 0);
			AGE_ASSERT(datas.head != elementNext);

			datas.head = element;
			datas.size += 1;

			__int64 comparandResult[2];
			comparandResult[0] = (__int64)oldDatas.size; /* low */
			comparandResult[1] = (__int64)oldDatas.head; /* high */
			if (_InterlockedCompareExchange128(
				&_datas.size,
				(__int64)datas.head,
				datas.size,
				&comparandResult[0]
				) == 1)
			{
				return;
			}
		}
	}