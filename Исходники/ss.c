void Combine( int Positions[], FILE *InputFiles[], int NumberInputs )
{
    int OddNibble ;
    BOOLEAN Odd ;
    int i ;
    int j ;
    G13 C[15] ;
    G13 c ;
    G13 Y[15] ;
    BOOLEAN FillNibbles( G13 *Nibbles, FILE *InputFiles[], int NumberInputs );

    setmode( fileno( stdout ), O_BINARY ) ;

    /* Compute the coefficients by which the nibbles from the
     * various input files can be combined to produce the output
     * file.
     *     If X(i) is the "position" of the ith input file, and
     * Y(i) is the value of a particular nibble in the ith file,
     * we will find coefficients C(i) such that
     * 
     *     p = C(1) * Y(1) + C(2) * Y(2) + ...
     * 
     * where p is the appropriate nibble for the output file.
     * 
     *     The formula for the Cs is:
     * 
     *     C(i) = product of (   X(j) / ( X(i) - X(j) )   ) for all j != i .
     * 
     * 
     */

    for ( i = 0; i < NumberInputs; i++ )
    {
     c = 1 ;
     for ( j = 0; j < NumberInputs; j++ )
         if ( j != i )
          c = Mult( c,
               Div( Positions[j], Positions[i] ^ Positions[j] ) ) ;
     C[i] = c ;
    }

    /*
     *  Now, process the input files:
     */

    Odd = TRUE ;
    while ( FillNibbles( Y, InputFiles, NumberInputs ) )
    {
     c = 0 ;
     for ( i = 0; i < NumberInputs; i++ )
         c ^= Mult( C[i], Y[i] ) ;

     if ( Odd )
         OddNibble = c ;
     else
         putchar( ( OddNibble << 4 ) | c ) ;

     Odd = !Odd ;
    }
}