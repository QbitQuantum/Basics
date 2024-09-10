/* Function to increment bus label members numbers,
 * i.e. when a text is ending with a number, adds
 * aIncrement to this number
 */
void IncrementLabelMember( wxString& name, int aIncrement )
{
    int  ii, nn;
    long number = 0;

    ii = name.Len() - 1; nn = 0;

    if( !isdigit( name.GetChar( ii ) ) )
        return;

    while( (ii >= 0) && isdigit( name.GetChar( ii ) ) )
    {
        ii--; nn++;
    }

    ii++;   /* digits are starting at ii position */
    wxString litt_number = name.Right( nn );

    if( litt_number.ToLong( &number ) )
    {
        number += aIncrement;
        name.Remove( ii ); name << number;
    }
}