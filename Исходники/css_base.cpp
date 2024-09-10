StyleListImpl::~StyleListImpl()
{
    StyleBaseImpl *n;

    if(!m_lstChildren) return;

    QListIterator<StyleBaseImpl*> it( *m_lstChildren );
    while ( it.hasNext() )
    {
        n = it.next();
        n->setParent(0);
        if( !n->refCount() ) delete n;
    }
    delete m_lstChildren;
}