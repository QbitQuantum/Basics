void wxSettableHeaderColumn::SetFlag(int flag)
{
    int flags = GetFlags();
    if ( !(flags & flag) )
        SetFlags(flags | flag);
}