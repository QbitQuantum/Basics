unsigned int Win32Popup::findInsertionPoint( unsigned int pos ) const
{
    // For this simple algorithm, we rely on the fact that in the final state
    // of the menu, the ID of each item is equal to its position in the menu
    int i = 0;
    while( i < GetMenuItemCount( m_hMenu ) &&
           GetMenuItemID( m_hMenu, i ) < pos )
    {
        i++;
    }
    return i;
}