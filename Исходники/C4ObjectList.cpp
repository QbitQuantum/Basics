void C4ObjectList::CompileFunc(StdCompiler *pComp, bool fSkipPlayerObjects, C4ValueNumbers * numbers)
{
	// "Object" section count
	int32_t iObjCnt = ObjectCount();
	pComp->Value(mkNamingCountAdapt(iObjCnt, "Object"));
	if (pComp->isDecompiler())
	{
		// skipping player objects would screw object counting in non-naming compilers
		assert(!fSkipPlayerObjects || pComp->hasNaming());
		// Decompile all objects in reverse order
		for (C4ObjectLink *pPos = Last; pPos; pPos = pPos->Prev)
			if (pPos->Obj->Status)
				if (!fSkipPlayerObjects || !pPos->Obj->IsUserPlayerObject())
					pComp->Value(mkNamingAdapt(mkParAdapt(*pPos->Obj, numbers), "Object"));
	}
	else
	{
		// FIXME: Check that no PlayerObjects are loaded when fSkipPlayerObjects is true
		// i.e. that loading and saving was done with the same flag.
		// Remove previous data
		Clear();
		// Load objects, add them to the list.
		for (int i = 0; i < iObjCnt; i++)
		{
			C4Object *pObj = NULL;
			try
			{
				pComp->Value(mkNamingAdapt(mkParAdapt(mkPtrAdaptNoNull(pObj), numbers), "Object"));
				Add(pObj, stReverse);
			}
			catch (StdCompiler::Exception *pExc)
			{
				// Failsafe object loading: If an error occurs during object loading, just skip that object and load the next one
				if (!pExc->Pos.getLength())
					LogF("ERROR: Object loading: %s", pExc->Msg.getData());
				else
					LogF("ERROR: Object loading(%s): %s", pExc->Pos.getData(), pExc->Msg.getData());
				delete pExc;
			}
		}
	}
}