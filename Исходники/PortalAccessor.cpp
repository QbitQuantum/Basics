void portal::SeekEndRoom( entityid p_room )
{
    BeginPath();
    while( IsValidPath() )
    {
        // exit out when you find a match
        if( CurrentEnd() == p_room )
            return;
        NextPath();
    }
}