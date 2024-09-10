void FramerateEqualizer::_exit()
{
    const Compound* compound = getCompound();
    if( !compound || _nSamples == 0 )
        return;

    const Compounds& children = compound->getChildren();

    EQASSERT( _loadListeners.size() == children.size( ));
    for( size_t i = 0; i < children.size(); ++i )
    {
        Compound*      child        = children[i];
        LoadListener&  loadListener = _loadListeners[i];
        
        LoadUnsubscriber unsubscriber( &loadListener );
        child->accept( unsubscriber );
    }
    
    _loadListeners.clear();
    _times.clear();
    _nSamples = 0;
}