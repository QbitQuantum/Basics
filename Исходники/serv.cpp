void 
SimpleFactory::updateVisibleIDs(Hashtable& result, UErrorCode& status) const 
{
    if (_visible) {
        result.put(_id, (void*)this, status); // cast away const
    } else {
        result.remove(_id);
    }
}