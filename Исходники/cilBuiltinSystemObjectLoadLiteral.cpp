/***************************************************************************
 *      Load array literal onto the stack
 ***************************************************************************/
void CSystemObject::LoadarrayLiteral( CCilVm* const pVm,
										   const int32_t iNumArguments, 
										   CVariable* pArguments )
{
	assert( pVm != NULL );
	//Array parameter can be null
	assert( iNumArguments >= 1 );

	//Skip this pointer
	pArguments++;

	//Create object object
	CVmObject* pObj = pVm->createObject( pVm->getArrayObjectRID() );
	CVariable var;
	var.setObjectRef( pObj );

	wchar_t strBuffer[ 22 ];		//22=max value width of longlong

	int32_t i = 0;
	for( ; i < iNumArguments - 1; ++i )
	{
		//Argument: 1) value of the property
		swprintf( strBuffer, 22, L"%d", i );
		var.refObject->setProperty( strBuffer, *pArguments );
		pArguments++;
	}

	//Set prototype: Array prototype object
	var.refObject->setPrototypeObject( 
		&pVm->getPrototypeObject( pVm->getArrayObjectRID() ) );

	//Update 'length' property
	CVariable varInt( 0 );
	var.refObject->setProperty( STRING_INTERNAL_LENGTH, varInt );
	//-2 means, 'prototype' & 'length'
	CVariable varLength( (int32_t)var.refObject->getPropertyMap().size() - 2,
						OPERAND_FLAG( OPERAND_FLAG_DONTDELETE | OPERAND_FLAG_DONTENUM ) ); 
	var.refObject->setProperty( STRING_INTERNAL_LENGTH, varLength );

	//Push the ObjectRef to a eval stack
	pVm->pushEvalStackVariable( var );

	return;
}