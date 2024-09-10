	// ***************************************************************************
	CInterfaceElement *CInterfaceElement::clone()
	{
		NLMISC::CMemStream dupStream;
		nlassert(!dupStream.isReading());
		CInterfaceGroup *oldParent = _Parent;
		_Parent = NULL;
		CInterfaceElement *oldParentPos = _ParentPos;
		CInterfaceElement *oldParentSize = _ParentSize;
		if (_ParentPos == oldParent) _ParentPos = NULL;
		if (_ParentSize == oldParent) _ParentSize = NULL;
		CInterfaceElement *begunThisCloneWarHas = NULL;
		try
		{
			if (dupStream.isReading())
			{
				dupStream.invert();
			}
			CInterfaceElement *self = this;
			dupStream.serialPolyPtr(self);
			std::vector<uint8> datas(dupStream.length());
			std::copy(dupStream.buffer(), dupStream.buffer() + dupStream.length(), datas.begin());
			dupStream.resetPtrTable();
			dupStream.invert();
			dupStream.fill(&datas[0], (uint32)datas.size());
			dupStream.serialPolyPtr(begunThisCloneWarHas);
		}
		catch(const NLMISC::EStream &)
		{
			// no-op -> caller has to handle the failure because NULL will be returned
		}
		//
		_Parent		  = oldParent;
		_ParentPos	  = oldParentPos;
		_ParentSize	  = oldParentSize;
		//
		return begunThisCloneWarHas;
	}