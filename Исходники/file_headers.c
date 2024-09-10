/*************************************************************
 * copyshort
 *------------------------------------------------------------
 * copy a 2-byte int, making sure to use the intended byte
 * order for the destination, regardless of what the
 * native byte order is on the current machine
 */
void copyshort( short int val, char *dest, char *intended )
{
    if ( strcmp( nativorder, intended ))
	swab((char *) &val, short_order.ch, 2 );
    else
	short_order.i2 = val;

    *dest++ = short_order.ch[0];
    *dest = short_order.ch[1];
}