Acad::ErrorStatus 
AsdkBody::applyPartialUndo(AcDbDwgFiler* filer, AcRxClass* classObj)
{
    if (AsdkBody::desc() != classObj)
        return AcDbEntity::applyPartialUndo( filer, classObj );

    Adesk::Int16 opCode;
    filer->readItem( &opCode );

    switch (opCode) 
    {
    case 555:  // It is a transformBy() operation
        {
        // filer->readBytes( &mat, sizeof AcGeMatrix3d );

        AcGeMatrix3d mat;
        AcGeVector3d x, y, z;
        AcGePoint3d  o;
    
        filer->readItem( &o );
        filer->readItem( &x );
        filer->readItem( &y );
        filer->readItem( &z );
    
        mat.setCoordSystem( o, x, y, z );
        mat.invert();
        transformBy( mat );
        }
        break;
    default:
        break;
    }
    return Acad::eOk;
}