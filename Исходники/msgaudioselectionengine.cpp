void MsgAudioSelectionEngine::HandleQueryCompletedL(CMdEQuery& aQuery,
        TInt aError)
    {
    iNameList.clear();
    iUriList.clear();
    if (aError == KErrCancel)
        {
        emit queryError(aError);
        return;
        }
    else
        {
        QMap<QString,QString> nameUriList;
        CMdEObjectQuery* query = static_cast<CMdEObjectQuery*> (&aQuery);
        TInt count = query->Count();
        for (TInt i = 0; i < count; ++i)
            {
            CMdEObject* object =
                    (CMdEObject*) query->TakeOwnershipOfResult(i);
            CleanupStack::PushL(object);
            CMdEPropertyDef& propDef = MsgAudioSelectionEngine::PropertyDefL(
                    iSession, MsgAudioSelectionEngine::EAttrFileName);

            CMdEProperty* property = 0;
            TInt err = object->Property(propDef, property, 0);
            if (err != KErrNotFound && property)
                {
                QString songName(XQConversions::s60DescToQString(
                        property->TextValueL()));
                QString uriValue(XQConversions::s60DescToQString(
                        object->Uri()));
                
                //insert into the map
                nameUriList.insertMulti(uriValue, songName);
                }
            CleanupStack::PopAndDestroy(object);
            }
        
        //now get all the song names and sort them
        iNameList = nameUriList.values();
        iNameList.sort();
        
        // go through the song list and get the associated uri
        // insert into the uri list
        int nameListTotal = iNameList.count();
        for(int nameListCount = 0; 
                nameListCount<nameListTotal;
                nameListCount++)
            {
            QString key = nameUriList.key(iNameList.at(nameListCount));
            iUriList.append(key);
            nameUriList.remove(key);                        
            }
        
        // emit the list to the model
        emit queryComplete(iNameList, iUriList);
        }
    }