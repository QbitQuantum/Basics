/*!
	Sends custom house to client
*/
static PyObject* wpMulti_sendcustomhouse( wpMulti* self, PyObject* args )
{
	Q_UNUSED(args);	
	if( !self->pMulti || self->pMulti->free || !self->pMulti->ishouse() )
		return PyFalse;
	
	if( !checkArgChar( 0 ) )
	{
		PyErr_BadArgument();
		return NULL;
	}
	P_PLAYER player = dynamic_cast<P_PLAYER>( getArgChar( 0 ) );
	if ( !player )
		return PyFalse;

//	self->pMulti->sendCH( player->socket() );
	cUOTxAskCustomHouse askch;

	askch.setSerial( self->pMulti->serial() );
	askch.setId( self->pMulti->revision() );

	player->socket()->send( &askch );

	return PyTrue;
}