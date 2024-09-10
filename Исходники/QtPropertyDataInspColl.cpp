QtPropertyDataInspColl::QtPropertyDataInspColl(void *_object, const DAVA::InspColl *_collection, bool autoAddChilds)
	: object(_object)
	, collection(_collection)
{
	if(NULL != collection && collection->Size(object) > 0 && autoAddChilds)
	{
		int index = 0;
		DAVA::MetaInfo *valueType = collection->ItemType();
		DAVA::InspColl::Iterator i = collection->Begin(object);
		while(NULL != i)
		{
			if(NULL != valueType->GetIntrospection())
			{
				void * itemObject = collection->ItemData(i);
				const DAVA::InspInfo *itemInfo = valueType->GetIntrospection(itemObject);

				if(NULL != itemInfo && NULL != itemObject)
				{
					QtPropertyData *childData = new QtPropertyDataIntrospection(itemObject, itemInfo);
					ChildAdd(QString::number(index), childData);
				}
				else
				{
					QString s;
					QtPropertyData* childData = new QtPropertyData(s.sprintf("[%p] Pointer", itemObject));
					childData->SetEnabled(false);
					ChildAdd(QString::number(index), childData);
				}
			}
			else
			{
				if(!valueType->IsPointer())
				{
					QtPropertyDataMetaObject *childData = new QtPropertyDataMetaObject(collection->ItemPointer(i), valueType);
					ChildAdd(QString::number(index), childData);
				}
				else
				{
					QString s;
					QtPropertyData* childData = new QtPropertyData(s.sprintf("[%p] Pointer", collection->ItemData(i)));
					childData->SetEnabled(false);

					if(collection->ItemKeyType() == DAVA::MetaInfo::Instance<DAVA::FastName>())
					{
						const DAVA::FastName *fname = (const DAVA::FastName *) collection->ItemKeyData(i);
						ChildAdd(fname->operator*(), childData);
					}
					else
					{
						ChildAdd(QString::number(index), childData);
					}
				}
			}

			index++;
			i = collection->Next(i);
		}
	}

	SetEnabled(false);
}