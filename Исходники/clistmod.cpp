static void RemoveProtoIconIndex(PROTOACCOUNT *pa)
{
	for (int i = 0; i < protoIconIndex.getCount(); i++)
		if (mir_strcmp(protoIconIndex[i].szProto, pa->szModuleName) == 0) {
			protoIconIndex.remove(i);
			break;
		}
}