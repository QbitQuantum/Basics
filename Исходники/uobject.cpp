/*!
	Removes an event handler from the object
*/
void cUObject::removeEvent( const QString& name )
{
	cPythonScript *event = 0;

	if( scriptChain && hasEvent( name ) )
	{
		unsigned int count = reinterpret_cast< unsigned int >( scriptChain[0] );

		if( count == 1 )
		{
			clearEvents();
		}
		else
		{
			unsigned int pos = 1;

			cPythonScript **newScriptChain = new cPythonScript*[ count ];
			newScriptChain[0] = reinterpret_cast< cPythonScript* >( count - 1 );

			for( unsigned int i = 1; i < count; ++i )
			{
				if( scriptChain[i]->name() != name ) {
					newScriptChain[pos++] = scriptChain[i];
				} else {
					event = scriptChain[i];
				}
			}

			delete [] scriptChain;
			scriptChain = newScriptChain;
		}
	}

	if( eventList_ != QString::null )
	{
		QStringList eventList = QStringList::split( ",", eventList_ );
		eventList.remove( name );
		eventList_ = eventList.join( "," );

		if( eventList_.isEmpty() )
			eventList_ = QString::null;
	}

	changed_ = true;

	if (event && event->canHandleEvent(EVENT_ATTACH)) {
		PyObject *args = Py_BuildValue("(N)", getPyObject());
		event->callEvent(EVENT_ATTACH, args);
		Py_DECREF(args);
	}
}