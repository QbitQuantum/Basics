void Range::checkNodeWOffset( DOM::Node n, int offset) const
{
    checkNode( n );
    
    if( offset < 0 )
        throw DOMException( DOMException::INDEX_SIZE_ERR );

    if( n.nodeType() != Node::TEXT_NODE )
    {
	if( (unsigned int)offset > n.childNodes().length() )
            throw DOMException( DOMException::INDEX_SIZE_ERR );
    }
    else
    {
	Text t;
	t = n;
        if( t.isNull() || (unsigned)offset > t.length() )
            throw DOMException( DOMException::INDEX_SIZE_ERR );
    }
}