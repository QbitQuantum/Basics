UtlBoolean 
DialByNameDB::getDigitStrings (
    const UtlString& displayName, 
    UtlSList& rDTMFStrings ) const
{
    UtlString lowerString = displayName;
    lowerString.toLower();
    lowerString = lowerString.strip(UtlString::both, '"');
    UtlTokenizer next( lowerString );
    UtlString token;
    UtlSList names;

    // Parse the Display name into a list of names
    // The algorithm for breaking up the string is as follows
    // if the string has > 2 tokens (forget about , separators)
    // create multiple entries in the IMDB for the all combinations
    // so for example
    // John Peter Smith Jr would result in DTMF entries for
    // PeterSmithJrJohn, SmithJrJohnPeter and JrJohnPeterSmith
    // @JC Added - separator for MIT's Avery-Smith example
   
    while (next.next(token, "\t\n,- ")) 
    {
        names.insert ( new UtlString ( token ) );
    }

    size_t numNames = names.entries();

    if ( numNames > 0 ) 
    {
        UtlString reorderedString;
        unsigned int splitPosition = 1;
        do 
        {
            unsigned int i;
            UtlString firstNames;
            for ( i=0; i<splitPosition; i++ ) 
            {
                firstNames += *(UtlString*)names.at(i);
            }

            UtlString lastNames;
            for ( i = splitPosition; i<numNames; i++) 
            {
                lastNames += *(UtlString*)names.at(i);
            }

            // add the new string
            reorderedString = lastNames + firstNames;

            unsigned int len = reorderedString.length();
            
            // calculate thd DTMF digits for the display name
            // firstly strip all , 's and spaces
            UtlString digitString;
            for ( i = 0; i<len; i++ )
            {
                int offset = (int) ( reorderedString(i) - 'a' );
                // filter out white space and comma separators
                if ( (offset >= 0) && (offset < 26) )
                    digitString += digitmap[ offset ];
            }

            rDTMFStrings.insert ( new UtlString (digitString) );

            splitPosition++;
        } while ( splitPosition<numNames );
    }

    // call the desctuctors on all the temp strings
    names.destroyAll();
    return TRUE;
}