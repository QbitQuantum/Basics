/***************************************************************************
 *   setStaticFieldFunctionObject
 ***************************************************************************/
bool CCilVm::setStaticFieldFunctionObject( const RID rid,
        const RID ridMethod )
{
    assert( TypeFromToken( ridMethod ) == MDT_METHODDEF );

    //Create function object and store it to static field
    CVmObject newobject;
    RID ridObj = getFunctionObjectRID();

    newobject.setRID( ridObj );
    newobject.setObjectName( getMetaData().getObjectNameRID( ridObj ) );
    newobject.setPrototypeObject( &getPrototypeObject( ridObj ) );
    newobject.setConstructorProperty( ridMethod );
    newobject.setCallProperty( ridMethod );

    getObjectPool().push_back( newobject );

    CVariable var;
    var.setObjectRef( &getObjectPool().back() );

    METHOD_DEF& method = getMetaData().getMethod( ridMethod );
    int32_t iLength = method.iNumArgments;
    assert( iLength >= 0 );

    CVariable varInt( iLength, OPERAND_FLAG_DONTENUM );
    var.refObject->setProperty( STRING_INTERNAL_LENGTH,
                                varInt );

    //Store the ObjectRef to a static field
    setStaticField( rid, var );

    return true;
}