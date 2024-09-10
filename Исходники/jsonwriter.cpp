/*!
 The type wxJSONTYPE_MEMORYBUFF is a \b wxJSON extension that is not correctly read by
 other JSON implementations.
 By default, the function writes such a type as an array of INTs as follows:
 \code
   [ 0,32,45,255,6,...]
 \endcode
 If the writer object was constructed using the \c wxJSONWRITER_MEMORYBUFF flag, then
 the output is much more compact and recognized by the \b wxJSON reader as a memory buffer
 type:
 \code
   '00203FFF06..'
 \endcode

*/
int
wxJSONWriter::WriteMemoryBuff( wxOutputStream& os, const wxMemoryBuffer& buff )
{
#define MAX_BYTES_PER_ROW	20
    char str[16];

    // if STYLED and SPLIT_STRING flags are set, the function writes 20 bytes on every row
    // the following is the counter of bytes written.
    // the string is splitted only for the special meory buffer type, not for array of INTs
    int bytesWritten = 0;
    bool splitString = false;
    if ( (m_style & wxJSONWRITER_STYLED) && 
               (m_style & wxJSONWRITER_SPLIT_STRING))   {
        splitString = true;
    }

    size_t buffLen = buff.GetDataLen();
    unsigned char* ptr = (unsigned char*) buff.GetData();
    wxASSERT( ptr );
    char openChar = '\'';
    char closeChar = '\'';
    bool asArray = false;

    if ( (m_style & wxJSONWRITER_MEMORYBUFF ) == 0 )  {
        // if the special flag is not specified, write as an array of INTs
        openChar = '[';
        closeChar = ']';
        asArray = true;
    }
    // write the open character
    os.PutC( openChar );

    for ( size_t i = 0; i < buffLen; i++ )  {
        unsigned char c = *ptr;
        ++ptr;

        if ( asArray )  {
            snprintf( str, 14, "%d", c );
            size_t len = strlen( str );
            wxASSERT( len <= 3 );
            wxASSERT( len >= 1 );
            str[len] = ',';
            // do not write the comma char for the last element
            if ( i < buffLen - 1 )    {
                ++len;
            }
            os.Write( str, len );
            if ( os.GetLastError() != wxSTREAM_NO_ERROR )    {
                return -1;
            }
        }
        else {
            // now convert the byte in two hex digits
            char c1 = c / 16;
            char c2 = c % 16;
            c1 += '0';
            c2 += '0';
            if ( c1 > '9' )  {
                c1 += 7;
            }
            if ( c2 > '9' )  {
                c2 += 7;
            }
            os.PutC( c1 );
            os.PutC( c2 );
            if ( os.GetLastError() != wxSTREAM_NO_ERROR )    {
                return -1;
            }
            if ( splitString )  {
                ++bytesWritten;
            }

            if (( bytesWritten >= MAX_BYTES_PER_ROW ) && ((buffLen - i ) >= 5 ))   {
                // split the string if we wrote 20 bytes, but only is we have to
                // write at least 5 bytes
                os.Write( "\'\n", 2 );
                int lastChar = WriteIndent( os, m_level + 2 );     // write indentation
                os.PutC( '\'' );               // reopen quotes
                if ( lastChar < 0 )  {
                    return lastChar;
                }
                bytesWritten = 0;
            }
        }
    }

    // write the close character
    os.PutC( closeChar );
    return closeChar;
}