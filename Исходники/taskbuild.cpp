void CTaskBuild::DeleteMark(Math::Vector pos, float radius)
{
    CObject*    pObj;
    Math::Vector    oPos;
    ObjectType  type;
    float       distance;
    int         i;

    CInstanceManager* iMan = CInstanceManager::GetInstancePointer();

    for ( i=0 ; i<1000000 ; i++ )
    {
        pObj = static_cast<CObject*>(iMan->SearchInstance(CLASS_OBJECT, i));
        if ( pObj == 0 )  break;

        type = pObj->GetType();
        if ( type != OBJECT_MARKSTONE   &&
             type != OBJECT_MARKURANIUM &&
             type != OBJECT_MARKKEYa    &&
             type != OBJECT_MARKKEYb    &&
             type != OBJECT_MARKKEYc    &&
             type != OBJECT_MARKKEYd    &&
             type != OBJECT_MARKPOWER   )  continue;

        oPos = pObj->GetPosition(0);
        distance = Math::Distance(oPos, pos);
        if ( distance <= radius )
        {
            pObj->DeleteObject();  // removes the mark
            delete pObj;
            i --;
        }
    }
}