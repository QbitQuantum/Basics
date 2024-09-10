void Widget::setTabOrder( int index )
{
    // negative = autonumber
    if (index < 0)
    {
        _tabOrder = 0;
        Widget *el = getTabGroup();
        while( _isTabGroup && el && el->getParent() )
            el = el->getParent();

        Widget *first=0, *closest=0;
        if (el)
        {
            // find the highest element number
            el->getNextWidget(-1, true, _isTabGroup, first, closest, true);
            if (first)
            {
                _tabOrder = first->getTabOrder() + 1;
            }
        }

    }
    else
        _tabOrder = index;
}