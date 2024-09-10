int32 PersistentEndXactRec_FetchObjectsFromSmgr(
	PersistentEndXactRecObjects	*objects,

	EndXactRecKind				endXactRecKind,

	int16						*objectCount)
{
	int32 serializeLen;

	int objKind;
	void *data;
	int32 count;
	int32 len;

	MemSet(objects, 0, sizeof(PersistentEndXactRecObjects));
	*objectCount = 0;
	serializeLen = 0;

	for (objKind = 1; objKind < MaxPersistentEndXactObjKind; objKind++)
	{
		data = NULL;
		count = 0;
		len = 0;
		switch (objKind)
		{
		case PersistentEndXactObjKind_FileSysAction:
			count = smgrGetPendingFileSysWork(
									endXactRecKind,
									(PersistentEndXactFileSysActionInfo**)&data,
									NULL);
			len = count * sizeof(PersistentEndXactFileSysActionInfo);

			PersistentEndXactRec_VerifyFileSysActionInfos(
										endXactRecKind,
										(PersistentEndXactFileSysActionInfo*)data,
										count);
			break;
			
		case PersistentEndXactObjKind_AppendOnlyMirrorResyncEofs:
			count = smgrGetAppendOnlyMirrorResyncEofs(
									endXactRecKind,
									(PersistentEndXactAppendOnlyMirrorResyncEofs**)&data);
			len = count * sizeof(PersistentEndXactAppendOnlyMirrorResyncEofs);
			break;

		default:
			elog(ERROR, "Unexpected persistent transaction object kind: %d",
				 objKind);
		}

		if (len > 0)
		{
			(*objectCount)++;

			serializeLen += offsetof(PersistentEndXactRecObjHdr, p.data) + len;

			PersistentEndXactRec_SetObjectInfo(
										objects, objKind, data, count, len);
		}
	}

	return serializeLen;
}