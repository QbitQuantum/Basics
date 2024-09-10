void CTaskSearch::DeleteMark(ObjectType type)
{
    CObject*    pObj;
    Math::Vector    oPos;
    int         i;

    CInstanceManager* iMan = CInstanceManager::GetInstancePointer();

    for ( i=0 ; i<1000000 ; i++ )
    {
        pObj = static_cast<CObject*>(iMan->SearchInstance(CLASS_OBJECT, i));
        if ( pObj == 0 )  break;

        if ( type == pObj->GetType() )
        {
            pObj->DeleteObject();  // removes the mark
            delete pObj;
            break;
        }
    }
}