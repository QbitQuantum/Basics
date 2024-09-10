///////////////////////////////////////////////////////////////////////////////
// Returns true if the specified item can be added to the array.  This is 
// determined by checking to make sure that the item derived from the common
// base class that was specified earlier.
// 
bool ClipboardElementArray::CanAdd( const Reflect::ObjectPtr& item ) const
{
    if ( !item.ReferencesObject() )
    {
        return false;
    }

    return item->IsA( GetCommonBaseClass() );
}