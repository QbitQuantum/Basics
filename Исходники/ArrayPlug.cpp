void ArrayPlug::inputChanged( Gaffer::Plug *plug )
{
	if( plug->parent<ArrayPlug>() != this )
	{
		return;
	}

	if( getInput() )
	{
		// When we ourselves have an input, we don't do any automatic addition or
		// removal of children, because the Plug base class itself manages
		// children to maintain the connection.
		return;
	}

	if( const ScriptNode *script = ancestor<ScriptNode>() )
	{
		if( script->currentActionStage() == Action::Undo ||
		    script->currentActionStage() == Action::Redo
		)
		{
			// If we're currently in an undo or redo, we don't
			// need to do anything, because our previous actions
			// will be in the undo queue and will be being replayed
			// for us automatically.
			return;
		}
	}

	if( plug->getInput() )
	{
		// Connection made. If it's the last plug
		// then we need to add one more.
		if( plug == children().back() && children().size() < m_maxSize )
		{
			PlugPtr p = getChild<Plug>( 0 )->createCounterpart( getChild<Plug>( 0 )->getName(), Plug::In );
			p->setFlags( Gaffer::Plug::Dynamic, true );
			addChild( p );
			MetadataAlgo::copyColors( getChild<Plug>( 0 ) , p.get() , /* overwrite = */ false );
		}
	}
	else
	{
		// Connection broken. We need to remove any
		// unneeded unconnected plugs so that we have
		// only one unconnected plug at the end.
		for( size_t i = children().size() - 1; i > m_minSize - 1; --i )
		{
			if( !getChild<Plug>( i )->getInput() && !getChild<Plug>( i - 1 )->getInput() )
			{
				removeChild( getChild<Plug>( i ) );
			}
			else
			{
				break;
			}
		}
	}
}