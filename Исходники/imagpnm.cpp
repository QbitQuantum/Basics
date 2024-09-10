bool wxPNMHandler::DoCanRead( wxInputStream& stream )
{
    Skip_Comment(stream);

    // it's ok to modify the stream position here
    if ( stream.GetC() == 'P' )
    {
        switch ( stream.GetC() )
        {
            case '2': // ASCII Grey
            case '3': // ASCII RGB
            case '5': // RAW Grey
            case '6': // RAW RGB
                return true;
        }
    }

    return false;
}