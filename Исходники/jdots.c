void showResults( List* resultsList, Item* resultsLevel )
{
    // Display header
    wprintf_s( TEXT( "    %19s %47s %12s %s\n" ),
        TEXT( "Date Modified" ),
        TEXT( "Coords" ),
        TEXT( "Size" ),
        TEXT( "Name" ) );

    wprintf_s( TEXT( "    %19s %47s %12s %s\n" ),
        TEXT( "-------------------" ),
        TEXT( "-----------------------------------------------" ),
        TEXT( "------------" ),
        TEXT( "--------------------------------" ) );

    // Display founded entries
    Traverse( resultsList, showItem );

    // Display totals
    wprintf_s( TEXT( "    %19s %47s %12s %s\n" ),
        TEXT( "-------------------" ),
        TEXT( "-----------------------------------------------" ),
        TEXT( "------------" ),
        TEXT( "--------------------------------" ) );

    showItem( resultsLevel );
}